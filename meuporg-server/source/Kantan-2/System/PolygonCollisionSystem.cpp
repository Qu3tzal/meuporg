#include "PolygonCollisionSystem.hpp"

namespace kantan
{
    bool SPCell::intersects(kantan::PolygonHitboxComponent* phc, sf::FloatRect AABB)
    {
        kantan::PolygonHitboxComponent phc_b(0, {});

        phc_b.points.push_back({AABB.left, AABB.top});
        phc_b.points.push_back({AABB.left + AABB.width, AABB.top});
        phc_b.points.push_back({AABB.left + AABB.width, AABB.top + AABB.height});
        phc_b.points.push_back({AABB.left, AABB.top + AABB.height});
        phc_b.computeAxes();

        sf::Vector2f _;
        return PolygonCollisionSystem::detectCollision(phc, &phc_b, _);
    }

    SPCell::SPCell(sf::FloatRect newAABB)
        : AABB(newAABB)
    {

    }

    SPCell::~SPCell()
    {

    }

    void SPCell::removeComponent(kantan::Component* ptr)
    {
        auto itr = std::find(components.begin(), components.end(), ptr);

        if(itr != components.end())
            components.erase(itr);
    }

	PolygonCollisionSystem::PolygonCollisionSystem()
    {
        // Default predicate.
        m_predicate = [](std::size_t, std::size_t){return true;};
    }

    bool PolygonCollisionSystem::detectCollision(kantan::PolygonHitboxComponent* a, kantan::PolygonHitboxComponent* b, sf::Vector2f& projectionVector)
    {
        std::vector<sf::Vector2f> all_axes;
        all_axes.reserve(a->axes.size() + b->axes.size());
        all_axes.insert(all_axes.end(), a->axes.begin(), a->axes.end());
        all_axes.insert(all_axes.end(), b->axes.begin(), b->axes.end());

        std::unique(all_axes.begin(), all_axes.end());

        projectionVector = sf::Vector2f(0.f, 0.f);

        float projectionVectorLength(std::numeric_limits<float>::max());

        for(sf::Vector2f& axe : all_axes)
        {
            float a_min_value(std::numeric_limits<float>::max()), a_max_value(std::numeric_limits<float>::min()),
                  b_min_value(std::numeric_limits<float>::max()), b_max_value(std::numeric_limits<float>::min());

            for(sf::Vector2f point : a->points)
            {
                float projection = dotProduct(point, axe) / dotProduct(axe, axe);

                if(projection < a_min_value)
                    a_min_value = projection;

                if(projection > a_max_value)
                    a_max_value = projection;
            }

            for(sf::Vector2f point : b->points)
            {
                float projection = dotProduct(point, axe) / dotProduct(axe, axe);

                if(projection < b_min_value)
                    b_min_value = projection;

                if(projection > b_max_value)
                    b_max_value = projection;
            }

            /*
                    _________
                        __________
            */
            if(a_min_value <= b_min_value && a_max_value <= b_max_value && a_max_value >= b_min_value)
            {
                sf::Vector2f wayOut = axe * (a_max_value - b_min_value);
                if(getLength(wayOut) < projectionVectorLength)
                {
                    projectionVector = wayOut;
                    projectionVectorLength = getLength(projectionVector);
                }
            }

            /*
                        ___________
                    _________
            */
            else if(b_min_value <= a_min_value && b_max_value <= a_max_value && b_max_value >= a_min_value)
            {
                sf::Vector2f wayOut = axe * (a_min_value - b_max_value);
                if(getLength(wayOut) < projectionVectorLength)
                {
                    projectionVector = wayOut;
                    projectionVectorLength = getLength(projectionVector);
                }
            }

            /*
                    ________________
                        _____
            */
            else if(a_min_value <= b_min_value && a_max_value >= b_max_value)
            {
                float by_right = b_min_value - a_max_value;
                float by_left = b_max_value - a_min_value;

                if(std::abs(by_left) < std::abs(by_right))
                {
                    if(std::abs(by_left) < projectionVectorLength)
                    {
                        projectionVector = axe * by_left;
                        projectionVectorLength = getLength(projectionVector);
                    }
                }
                else
                {
                    if(std::abs(by_right) < projectionVectorLength)
                    {
                        projectionVector = axe * by_right;
                        projectionVectorLength = getLength(projectionVector);
                    }
                }
            }

            /*
                        _____
                    ________________
            */
            else if(b_min_value <= a_min_value && b_max_value >= a_max_value)
            {
                float by_right = b_min_value - a_max_value;
                float by_left = b_max_value - a_min_value;

                if(std::abs(by_left) < std::abs(by_right))
                {
                    if(std::abs(by_left) < projectionVectorLength)
                    {
                        projectionVector = axe * by_left;
                        projectionVectorLength = getLength(projectionVector);
                    }
                }
                else
                {
                    if(std::abs(by_right) < projectionVectorLength)
                    {
                        projectionVector = axe * by_right;
                        projectionVectorLength = getLength(projectionVector);
                    }
                }
            }

            /*
                    ___
                        ____

                or
                        ____
                    ___
            */
            else
            {
                projectionVector = sf::Vector2f(0.f, 0.f);
                return false;
            }
        }

        return true;
    }

    void PolygonCollisionSystem::onComponentRemoved(kantan::Component* component)
    {
        // The component may be living in multiple cells.
        for(std::size_t i(0) ; i < m_cellMap.size() ; i++)
            for(std::size_t j(0) ; j < m_cellMap[i].size() ; j++)
                m_cellMap[i][j].removeComponent(component);
    }

    void PolygonCollisionSystem::onComponentAdded(kantan::Component* component)
    {
        kantan::PolygonHitboxComponent* hitbox = static_cast<kantan::PolygonHitboxComponent*>(component);

        for(std::size_t i(0) ; i < m_cellMap.size() ; i++)
        {
            for(std::size_t j(0) ; j < m_cellMap[i].size() ; j++)
            {
                if(SPCell::intersects(hitbox, m_cellMap[i][j].AABB))
                {
                    m_cellMap[i][j].components.push_back(component);
                }
            }
        }
    }

    void PolygonCollisionSystem::initSpatialPartitioning(sf::Vector2i cellMapSize, float cellSize, sf::Vector2f cellMapOffset)
    {
        m_cellMapSize = cellMapSize;
        m_cellSize = cellSize;
        m_cellMapOffset = cellMapOffset;

        for(int i(0) ; i < cellMapSize.x ; i++)
        {
            m_cellMap.push_back(std::vector<SPCell>());

            for(int j(0) ; j < cellMapSize.y ; j++)
            {
                sf::FloatRect AABB;
                AABB.left = cellMapOffset.x + cellSize * i;
                AABB.top = cellMapOffset.y + cellSize * j;
                AABB.width = cellSize;
                AABB.height = cellSize;

                m_cellMap[i].push_back(SPCell(AABB));
            }
        }
    }

    void PolygonCollisionSystem::updateSpatialPartitioning()
    {
        // Check for each cell if the component is still in the right cells.
        for(std::size_t i(0) ; i < m_cellMap.size() ; i++)
        {
            for(std::size_t j(0) ; j < m_cellMap[i].size() ; j++)
            {
                for(kantan::Component* component : m_cellMap[i][j].components)
                {
                    kantan::PolygonHitboxComponent* hitbox = static_cast<kantan::PolygonHitboxComponent*>(component);

                    // If the component does not intersects with its own cell anymore, remove and reinsert it.
                    if(!SPCell::intersects(hitbox, m_cellMap[i][j].AABB))
                    {
                        onComponentRemoved(component);
                        onComponentAdded(component);
                    }
                }
            }
        }
    }

    // Update.
    void PolygonCollisionSystem::update(sf::Time elapsed, std::vector<kantan::Component*>& polygonHitboxComponents, std::vector<kantan::Component*>& movementComponents)
    {
        m_collisions.clear();

        // If spatial partitioning is disabled.
        if(m_cellMapSize == sf::Vector2i(0, 0))
            return resolveCollisions(elapsed, polygonHitboxComponents, movementComponents); // return void.

        // Spatial partitioning.
        updateSpatialPartitioning();

        // Resolve collisions per cell.
        for(std::size_t i(0) ; i < m_cellMap.size() ; i++)
            for(std::size_t j(0) ; j < m_cellMap[i].size() ; j++)
                resolveCollisions(elapsed, m_cellMap[i][j].components, movementComponents);
    }

    void PolygonCollisionSystem::resolveCollisions(sf::Time elapsed, std::vector<kantan::Component*>& polygonHitboxComponents, std::vector<kantan::Component*>& movementComponents)
    {
		m_collisions.clear();

        // We check each hitbox component against all the overs.
        /// /!\ It's a naive and slow way of doing it.
        for(kantan::Component* component : polygonHitboxComponents)
        {
            kantan::PolygonHitboxComponent* fstHitbox = static_cast<kantan::PolygonHitboxComponent*>(component);

            // If this entity has no movement, it's not the one to modify.
            // We look for the corresponding movement component, if it exists.
            kantan::MovementComponent* fstMovement = Component::getFirstComponentOwnedBy<kantan::MovementComponent>(fstHitbox->getOwnerId(), movementComponents);

            // If none found, next hitbox component.
            if(fstMovement == nullptr)
                continue;

            // Apply the movement.
            fstMovement->velocity += fstMovement->acceleration * elapsed.asSeconds();

            // Reset the acceleration.
            fstMovement->acceleration = sf::Vector2f(0.f, 0.f);

            // Check we don't exceed the maximum speed.
            if(fstMovement->maximumSpeed >= 0.f && kantan::getLength(fstMovement->velocity) > fstMovement->maximumSpeed)
                fstMovement->velocity = kantan::normalize(fstMovement->velocity) * fstMovement->maximumSpeed;

            // Create a transformation with the projection vector.
            sf::Transform transform;
            transform.translate(fstMovement->velocity * elapsed.asSeconds());

            // Apply the movement transformation.
            for(std::size_t i(0) ; i < fstHitbox->points.size() ; i++)
                fstHitbox->points[i] = transform.transformPoint(fstHitbox->points[i]);

            for(kantan::Component* component : polygonHitboxComponents)
            {
                kantan::PolygonHitboxComponent* sndHitbox = static_cast<kantan::PolygonHitboxComponent*>(component);

                // Do not check against yourself.
                if(fstHitbox == sndHitbox)
                    continue;

                // The projection vector in case of a collision.
                sf::Vector2f projectionVector;

                // Is there a collision ?
                if(detectCollision(fstHitbox, sndHitbox, projectionVector))
                {
                    // Are we blocking ?
					// And do we satisfy the predicate ?
                    if(fstHitbox->isBlocking && sndHitbox->isBlocking && m_predicate(fstHitbox->getOwnerId(), sndHitbox->getOwnerId()))
                    {
                        // Create a transformation with the projection vector.
                        transform = sf::Transform::Identity;
                        transform.translate(-projectionVector);

                        // Apply the movement transformation.
                        for(std::size_t i(0) ; i < fstHitbox->points.size() ; i++)
                            fstHitbox->points[i] = transform.transformPoint(fstHitbox->points[i]);

                        // Bouncing.
                        /*
                        if(projectionVector != sf::Vector2f(0.f, 0.f))
                            fstMovement->velocity = 0.2f * getLength(fstMovement->velocity) * normalize(-projectionVector / elapsed.asSeconds());
                        */

                        // Too small velocities must be canceled.
                        if(getLength(fstMovement->velocity) <= 0.1f)
                            fstMovement->velocity = sf::Vector2f(0.f, 0.f);

                        // Register the collision.
                        m_collisions.push_back(std::make_tuple(fstHitbox->getOwnerId(), sndHitbox->getOwnerId(), projectionVector));
                    }
                }
            }
        }
    }

    // Returns the collisions record.
    std::vector<std::tuple<std::size_t, std::size_t, sf::Vector2f>> PolygonCollisionSystem::getCollisionRecord()
    {
        return m_collisions;
    }

    // Returns hitboxes near a position.
    std::vector<kantan::Component*> PolygonCollisionSystem::getNear(sf::Vector2f position, float radius)
    {
        // Early check.
        if(radius <= 0.f)
            return {};

        // Hitboxes list.
        std::vector<kantan::Component*> hitboxes;

        // Check how many cells around we need to look in.
        int cellsAround = std::ceil(radius / m_cellSize);

        // Check in which cell the position is.
        sf::Vector2i centerCell(position.x / m_cellSize, position.y / m_cellSize);

        // Start the search.
        float squaredRadius = radius * radius;
        for(int x(-cellsAround) ; x < cellsAround ; x++)
        {
            for(int y(-cellsAround) ; y < cellsAround ; y++)
            {
                // Compute which cell we are looking at.
                sf::Vector2i cellPosition = centerCell + sf::Vector2i(x, y);

                // Security checks.
                cellPosition.x = std::max(0, cellPosition.x);
                cellPosition.x = std::min(m_cellMapSize.x - 1, cellPosition.x);
                cellPosition.y = std::max(0, cellPosition.y);
                cellPosition.y = std::min(m_cellMapSize.y - 1, cellPosition.y);

                // We now can look at the cell.
                for(kantan::Component* component : m_cellMap[cellPosition.x][cellPosition.y].components)
                {
                    kantan::PolygonHitboxComponent* phc = component->convert<kantan::PolygonHitboxComponent>();
                    sf::Vector2f center = kantan::getCenter<float>(phc->points);

                    float squaredDistance = kantan::squaredEuclidianDistance(position, center);

                    // If the hitbox is in the radius, we keep it.
                    if(squaredDistance < squaredRadius)
                    {
                        hitboxes.push_back(component);
                    }
                }
            }
        }

        // Return the hitboxes list.
        return hitboxes;
    }

	// Sets the collision response predicate.
    void PolygonCollisionSystem::setCollisionResponsePredicate(std::function<bool(std::size_t, std::size_t)> predicate)
    {
        m_predicate = predicate;
    }
} // namespace kantan.

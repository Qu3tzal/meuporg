
template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	// Create and load resource
	std::unique_ptr<Resource> resource(new Resource());
	if(!resource->loadFromFile(filename))
        #ifdef KANTAN_ANDROID
        std::exit(1);
        #else
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
        #endif // KANTAN_ANDROID

	// If loading successful, insert resource to map
	insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParam)
{
	// Create and load resource
	std::unique_ptr<Resource> resource(new Resource());
	if(!resource->loadFromFile(filename, secondParam))
		#ifdef KANTAN_ANDROID
        std::exit(1);
        #else
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
        #endif // KANTAN_ANDROID

	// If loading successful, insert resource to map
	insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = m_resourceMap.find(id);
	assert(found != m_resourceMap.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = m_resourceMap.find(id);
	assert(found != m_resourceMap.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> resource)
{
	// Insert and check success
	auto inserted = m_resourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::unload(Identifier id)
{
    auto found = m_resourceMap.find(id);
	assert(found != m_resourceMap.end());

    m_resourceMap.erase(found);
}

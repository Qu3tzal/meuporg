#ifndef KANTAN_COMPONENT
#define KANTAN_COMPONENT

#include <string>
#include <vector>
#include <algorithm>

namespace kantan
{
	/**
		Component class.
	**/
	class Component
	{
        public:
            // Returns the component with the same owner id.
            // Returns nullptr if none.
            template<typename T>
            static T* getFirstComponentOwnedBy(unsigned long long ownerId, std::vector<kantan::Component*>& components)
            {
                // We look for the corresponding component, if it exists.
                auto cItr = std::find_if(components.begin(),
                                          components.end(),
                                          [ownerId](kantan::Component* c) {
                                            return c->getOwnerId() == ownerId;
                                          });

                // If none found, returns nullptr.
                if(cItr == components.end())
                    return nullptr;

                return static_cast<T*>(*cItr);
            }

            template<typename T>
            T* convert()
            {
                return static_cast<T*>(this);
            }

		public:
			// Ctor.
			Component(std::string name = "Unknown", unsigned long long ownerId = (-1));

			// Dtor.
			virtual ~Component();

			// Name.
			std::string getName() const;

			// Owner id.
			unsigned long long getOwnerId() const;

		protected:
		    // The name of the component.
			std::string m_name;

			// The id of the entity owning the component.
            unsigned long long m_ownerId;
	};

} // namespace kantan.

#endif // KANTAN_COMPONENT

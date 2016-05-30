#ifndef KANTAN_DELETIONMARKERCOMPONENT
#define KANTAN_DELETIONMARKERCOMPONENT

#include "Component.hpp"

namespace kantan
{
    /*
        Deletion marker component.
    */
    class DeletionMarkerComponent : public kantan::Component
    {
        public:
            // Ctor.
            DeletionMarkerComponent(std::size_t ownerId);

            // Attribute.
            bool marked;
    };
} // namespace kantan.

#endif // KANTAN_DELETIONMARKERCOMPONENT

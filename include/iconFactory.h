// TODO
// Finish the declaration of IconFactory that
// 1. offers some methods to create an Icon.
// 2. encapsulates the constructor from the caller.

#include "RPSGameObject.h"
#include "icon.h"

class IconFactory : public Icon {
  public:
	IconFactory(){};
	Icon *create_icon(RPSType type) const;
};

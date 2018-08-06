#ifndef FSEGTACURSORCONTROLLER_DEFINED_H
#define FSEGTACURSORCONTROLLER_DEFINED_H

#include <memory>

using namespace std;

namespace FlameSteelCore {

class Object;

};

namespace FlameSteelEngine {
namespace GameToolkit {
namespace Algorithms {

class CursorController;

};
};
};

using namespace FlameSteelCore;

namespace FlameSteelEngine {
namespace GameToolkit {
namespace Algorithms {

class CursorControllerDelegate {
public:
	virtual void cursorControllerDidUpdateCursor(CursorController *cursorController, shared_ptr<Object> cursor);
};
};
};
};

#endif

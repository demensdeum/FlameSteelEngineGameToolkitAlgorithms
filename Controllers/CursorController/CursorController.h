#ifndef FSEGTACURSORCONTROLLER_ENABLED
#define FSEGTACURSORCONTROLLER_ENABLED

#include <FlameSteelFramework/FlameSteelCore/Controller.h>

namespace FlameSteelCore {
class Object;
};

class FSEGTInputController;

using namespace FlameSteelCore;

namespace FlameSteelEngine {
namespace GameToolkit {
namespace Algorithms {

class CursorControllerDelegate;

class CursorController: public Controller, public enable_shared_from_this<CursorController> {

public:
	CursorController(shared_ptr<Object> cursor, shared_ptr<FSEGTInputController> inputController);
	virtual void step();
	weak_ptr<CursorControllerDelegate> delegate;

private:
	shared_ptr<Object> cursor;
	shared_ptr<FSEGTInputController> inputController;
};

};
};
};

#endif
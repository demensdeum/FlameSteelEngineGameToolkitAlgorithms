#include "CursorControllerDelegate.h"
#include <iostream>

using namespace FlameSteelEngine::GameToolkit::Algorithms;

void CursorControllerDelegate::cursorControllerDidUpdateCursor(CursorController *cursorController, shared_ptr<Object> cursor) {

	cout << "Unused void cursorControllerDidUpdateCursor(shared_ptr<CursorController> cursorController, shared_ptr<Object> cursor)" << endl;

};

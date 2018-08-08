#include <iostream>
#include "CursorController.h"
#include <FlameSteelEngineGameToolkit/Utils/FSEGTUtils.h>
#include <FlameSteelEngineGameToolkit/IO/Input/FSEGTInputController.h>
#include <FlameSteelEngineGameToolkitAlgorithms/Controllers/CursorController/CursorControllerDelegate.h>

using namespace FlameSteelEngine::GameToolkit::Algorithms;

CursorController::CursorController(shared_ptr<Object> cursor, shared_ptr<FSEGTInputController> inputController) {
	this->cursor = cursor;
	this->inputController = inputController;
	this->delegate = delegate;
}

void CursorController::step() {

	auto pointerXdiff = inputController->getPointerXdiff();
	auto pointerYdiff = inputController->getPointerYdiff();

	auto position = FSEGTUtils::getObjectPosition(cursor);
	position->x += pointerXdiff / 1000.0f;
	position->y += -pointerYdiff / 1000.0f;

	auto delegateObject = delegate.lock();

	if (delegateObject.get() != nullptr) {

		delegateObject->cursorControllerDidUpdateCursor(shared_from_this(), cursor);
	}
};
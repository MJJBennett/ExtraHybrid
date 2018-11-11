#include "CloseWindow.h"

CallType CloseWindow::operator()() {
    subject_->close();
    return CallType::None;
}

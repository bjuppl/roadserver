#include "control.h"

Control *Control::instance_ = NULL;

Control &Control::instance() {
    if  (instance_ == NULL ) {
        instance_ = new Control();
    }
    return *instance_;
}

void Control::launch() {

}

void Control::launch(string id ) {

}

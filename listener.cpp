#include "listener.h"

Switchboard *Switchboard::instance_ = NULL;
Switchboard &Switchboard::instance() {
    if ( instance_ == NULL ) {
        instance_ = new Switchboard;
    }
    return *instance_;
}

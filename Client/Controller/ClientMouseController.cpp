#include "ClientMouseController.h"

ClientMouseController::ClientMouseController(std::unordered_map<MouseButtons, std::function<void()>>&& mouseMap) :_mouseMap{std::move(mouseMap)}
{
}

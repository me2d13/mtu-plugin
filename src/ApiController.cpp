#include "ApiController.h"
#include "global.h"
#include "json.hpp"


ApiResponse ApiController::handleRequest(std::string request) {
	// check if request is for xpl
	if (request == "xpl") {
		return { true, handleXplRequest(), 200 };
	}
	// request not handled
	return { false, "", 400 };
}

std::string ApiController::handleXplRequest() {
	nlohmann::json j;
	j["elevator_trim"] = glb()->getXplData()->getElevatorTrimValue();
	j["in_flight"] = glb()->getXplData()->isInFlight();
	j["aircraft"] = glb()->getXplData()->getAircraft();
	return j.dump();
}
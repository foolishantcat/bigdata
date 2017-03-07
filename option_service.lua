option_service = {}
local M = option_service

-- OS: ios/android/win
-- version: x.x.x
function M:version()
    return "ios", "0.0.1"
end

function M:execute()
    return "option_service for ok";
end

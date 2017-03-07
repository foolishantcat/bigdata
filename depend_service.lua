depend_service = {}
local M = depend_service

-- OS: ios/android/win
-- version: x.x.x
function M:version()
    return "ios", "0.0.1"
end

function M:execute()
    return "depend_service for ios ok",0;
end

function M:login(user)
    return "login ok."..user;
end

function M:logout(user)
    return "logout ok."..user;
end

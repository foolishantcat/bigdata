-- config.lua
config = {}
local M=config

-- 每个module必须实现
-- OS: any/ios/android/win
-- version: x.x.x
function M:version()
    return "ios", "0.0.1"
end

local urlprefix="http://192.168.0.252/ios/"

-- 依赖的业务文件
M.depend = {
    -- {"filename", "version", "md5"},
    {"depend_service.lua", "0.0.1", "51a562e05cfcf1f4cbf1fd4f6a57e623"},
}

-- 可选的业务文件
M.option = {
    -- {"filename", "version", "md5"},
    {"option_service-ios.lua", "0.0.1", "aa2d13b593be084c26178d2611caf5b8"},
}

function test(str)
	return str
end

print("execute config ok")

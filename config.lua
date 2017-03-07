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
    {"depend_service.lua", "0.0.1", "bb4d8ad4b1e88a8d674cfee5fd38be62"},
}

-- 可选的业务文件
M.option = {
    -- {"filename", "version", "md5"},
    {"option_service.lua", "0.0.1", "5592910d495e77a57e198e672b26d97e"},
}

M.cmdstring = {
    {"login", "depend_service:login"},
    {"logout", "depend_service:logout"},
}

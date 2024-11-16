#target extended-remote :3333
target extended-remote :4242
monitor reset
monitor halt
set remotetimeout 60000
set mem inaccessible-by-default off
set arm force-mode thumb
define hook-quit
    set confirm off
end
set print elements 1024
load

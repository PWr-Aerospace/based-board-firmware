# How to debug your awesome shit?

- **ACHTUNG** - Make sure you have openocd and gdb installed!
- **ACHTUNG#2** - The program to be debugged should be compiled with -g option!
- **ACHTUNG#3** - Some operations (especially server running) may need root user - the try `sudo su`  ;)

## Step by step debugging
-- 1. Connect debugger module to the board
-- 2. Server running* - Open terminal and run following command:
`openocd -f <PATH-TO-STLINK-CONFIG> -f <PATH-TO-PROPER-STM32-CONFIG>`
For example:
`openocd -f /usr/local/share/openocd/scripts/interface/stlink-v2-1.cfg -f /usr/local/share/openocd/scripts/target/stm32l4x.cfg`
Note, that there is possible that `stlink-v2.cfg` does not work - then try to use `stlink-v2-1.cfg`
-- 3. Open another terminal and cd binary file destination
For example:
`cd /Users/tobiaszpuslecki/Desktop/OBC-prototype-L476/build/build/bin`
-- 4. Then you can finally run `gdb` with command:
`(echo "target remote localhost:<PORT>"; cat) | arm-none-eabi-gdb <BINARY-NAME>`
For example:
`(echo "target remote localhost:3333"; cat) | arm-none-eabi-gdb hello_world`
-- 5. Now it's time for real fun
--- Restart the uC and stop code execution - `monitor reset halt`,
--- Load code to uC - `load`,
--- Now you can debug your firmware exactly like computer program** <3 

Example session:
(gdb) info br              # info about breakpoints
(gdb) br main.c:30    # set breakpoint at line 30 of main.c
(gdb) bt                     # show backtrace
(gdb) br delay_ms    # set breakpoint at delay_ms function
(gdb) c                      # run program - it will be stopped on nearly breakpoint





* Another way to run GDB server on port 4500 and connect to it:
$> st-util -p <PORT>
$> gdb
(gdb)> target extended-remote localhost:<PORT>

** Link to gdb tutorial -  https://www.geeksforgeeks.org/gdb-command-in-linux-with-examples/

# var_show.tcl

# This HAL file can be used to show context and
# INI variable arrays available to Tcl HAL file.
# Example: [HAL]LIB:var_show.tcl arg1 arg2

#begin-----------------------------------------------------------------
source [file join $::env(HALLIB_DIR) util_lib.tcl]

show_ini
show_context

puts ::argv=$::argv
puts ::arglen=[llength $::argv]

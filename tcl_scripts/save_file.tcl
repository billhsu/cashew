set types {
        {"Cashew Files"     {.cashew}    }
        {"All files"                    *}
}
proc doIt {label} {
    global types   
    set file [tk_getSaveFile -filetypes $types -parent .]
    $label configure -text $file
    puts $file
    exit 0
}
proc center_the_toplevel { w } {

    # Callback on the <Configure> event for a toplevel
    # that should be centered on the screen

    # Make sure that we aren't configuring a child window

    if { [string equal $w [winfo toplevel $w]] } {

        # Calculate the desired geometry

        set width 300
        set height 60
        set x [expr { ( [winfo vrootwidth  $w] - $width  ) / 2 }]
        set y [expr { ( [winfo vrootheight $w] - $height ) / 2 }]

        # Hand the geometry off to the window manager

        wm geometry $w ${width}x${height}+${x}+${y}

        # Unbind <Configure> so that this procedure is
        # not called again when the window manager finishes
        # centering the window
        bind $w <Configure> {}

    }

    return
}

label .l  -text "No File"
button .b1 -width 10 -text "Save File?" \
        -command "doIt .l"
button .b2 -width 10 -text "Cancel" \
        -command "exit 0"

grid .b1 -row 0 -column 0
grid .b2 -row 1 -column 0
grid .l -row 0 -column 1

wm title . "Save File"
center_the_toplevel .
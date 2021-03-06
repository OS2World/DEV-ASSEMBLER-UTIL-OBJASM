OBJASM version 2.0
------------------
The file OBJUNARC.EXE is a self-extracting archive (ala LHARC). To extract
OBJASM from its compressed form, execute OBJUNARC.EXE.

Versions 2.0's enhancements are as follows:

    1.  80186, 80286, 80386, 80486 with corresponding 80x87 support.

    2.  OS/2 support.  OBJASM now works with OS/2 .OBJ files, excluding
        import libaries, since MASM doesn't have a method of declaring
        imports or exports.  The file OBJASM.EXE, itself is a bound
        executable, able to execute in DOS, or in OS/2.

    3.  The additional information file (a new feature) is now able to
        control how segments are dis-assembled on an entire segment basis,
        and on an individual byte basis.  Also, internal labels can be
        generated and named.

    4.  Better label/symbol generation.  Now the size that corresponds to
        the symbol is saved and any instructions which reference that
        symbol get the appropriate prefix (word ptr, byte ptr, etc) only
        if the size is in-appropriate.  Also, there are some instructions
        which require the prefix.

    5.  Instructions which span object module records are now detected and
        handled so that the output file looks just as it did when it was
        assembled/compiled.

    6.  Data variables are output with the appropriate "db","dw","dd", etc.
        Previously, the size of the data was not known. Now that it is known
        (see 4. above) it makes the data segments look much nicer.

    7.  Segments other than "CODE" are now dis-assembled as code segments.
        The new rule is any segment which has a class name of CODE or DRIVER,
        or has a segment name of CODE, or has a segment name with the word
        TEXT in it, will be dis-assembled as a code segment.  The use of
        a segment specifier in the additional information file will overide
        this determination.

    8.  The fixup frame information is now computed correctly.  OBJASM now
        produces "assume" directives dynamically to help MASM know what
        to do.  The "frame" is normally the segment which a fixup is
        taken relative to.  For example:
                mov     ax,offset DGROUP:myvar
        In this statement the offset of myvar is taken relative to the
        group DGROUP.  DGROUP is the frame.

    9.  Some sequences of instructions dis-assembled could cause the message
        "Dis-assembly Record Over-run".  The main cause of this message has
        been removed.  Should you get this message in the future, please
        contact us.

Please read OBJASM.DOC for a more complete description of the command line
arguments and the additional information file.

Below is part of the standard README file from the previous released version:
----------------------------------------------------------------------------

Version 1.3 Enhancements:

    1.  Support for the 80x87 coprocessor instructions.

    2.  Proper handling of the RET/RETF (return and return far) instructions.
        This caused the addition of the command line option -4 which allows
        OBJASM to be strictly MASM v4.0 compatible.  If you have MASM v5.0
        or greater, this option can be ignored.

    3.  The JNB/JB instruction orders were reversed and improper.  They are
        correct now.

    4.  Some of the addressing modes did not work when fixup's occurred
        for the operands.  Also, mis-aligned fixups are now detected.

    5.  External definitions are now listed in the segment where they were
        declared.  External definitions which are never used are listed
        at the beginning (where they were before).  This produces a nice
        external definitions list at the beginning of each code segment.

    6.  The old variable buff_limit was divided into two variables. They
        are called 'code_string' and 'data_string'.  This allows the
        string detection routine to operate better on both code segments and
        data segments.

    7.  MS new local record types are now handled.  The record types are
        LEXTDEF, LPUBDEF (both), and LCOMDEF.  We didn't know how to make
        MS C v5.0 generate LPUBDEF or LCOMDEF records, but we did handle
        them.  We were able to handle and test the LEXTDEF records.  Local
        publics, communals, and externals will appear commented out with
        prefix ';Static'.  For example:

                  EXTRN   myvar1
                  EXTRN   myvar2
          ;Static EXTRN   myvar3     ; This is a static external
                  EXTRN   myvar4

    8.  A command line option -r was added to produce RASM86 compatible
        assembly language (.A86 files instead of .ASM files).  The 
        translation is actually better than that for MASM (it was easier 
        because RASM86 is not as complicated as MASM).  Now, OBJASM can
        be used to convert .A86 files to .ASM files and vice versa.

    9.  A command line option -a was added.  This option allows OBJASM
        to create labels to make the output look better.  This option
        is very useful in conjunction with .OBJ files created by EXEOBJ.

   10.  A command line option -h was added.  This option allows OBJASM
        to put hex dump comments on most of the instructions dis-assembled.
        The will display the address (relative to beginning of segment)
        followed by the bytes that make up the instruction.

   11.  Tab positioning for output was normalized.  It is still not perfect,
        but it is better than it was!

   12.  Only segments with the class named "CODE" are now scanned for
        instructions.  The name "CODE" was is used by most of the high
        level compilers, so we thought it would be safe.  If this becomes
        a problem (i.e. you have instructions in your data segments, please
        contact us).

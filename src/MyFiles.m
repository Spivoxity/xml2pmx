MODULE MyFiles;

IMPORT Files;

TYPE File* =
  POINTER TO RECORD
    native: Files.File;
    current: INTEGER;
  END;

TYPE Rider* =
  RECORD
    base: File;
    id: INTEGER;
    eof-: BOOLEAN;
  END;

VAR stamp: INTEGER;

PROCEDURE Open(name, mode: ARRAY OF CHAR): File;
  VAR f: File; g: Files.File;
BEGIN
  g := Files.Open(name, mode);
  IF g = NIL THEN
    RETURN NIL
  ELSE
    NEW(f);
    f.native := g; f.current := 0;
    RETURN f
  END
END Open;

PROCEDURE New*(name: ARRAY OF CHAR): File;
BEGIN
  RETURN Open(name, "w+")
END New;

PROCEDURE Old*(name: ARRAY OF CHAR): File;
BEGIN
  RETURN Open(name, "r")
END Old;

(* End of file behaviour: EOF is initially false; trying to read beyond the
   end of the file returns a CHR(0) and sets the EOF flag. *)

PROCEDURE Set*(VAR r: Rider; f: File; off: INTEGER);
BEGIN
  Files.Seek(f.native, off, Files.SeekSet);
  r.base := f;
  r.eof := FALSE;

  stamp := stamp+1;
  r.id := stamp;
  f.current := stamp;
END Set;

PROCEDURE Read*(VAR r: Rider; VAR ch: CHAR);
  VAR f: File;
BEGIN
  f := r.base;
  ASSERT(f.current = r.id);
  IF Files.Eof(f.native) THEN
    ch := CHR(0); r.eof := TRUE
  ELSE
    Files.ReadChar(f.native, ch)
  END
END Read;

PROCEDURE Write*(VAR r: Rider; ch: CHAR);
BEGIN
  ASSERT(r.base.current = r.id);
  Files.WriteChar(r.base.native, ch)
END Write;

PROCEDURE WriteBytes*(VAR r: Rider; buf: ARRAY OF CHAR; len: INTEGER);
  VAR i: INTEGER;
BEGIN
  ASSERT(r.base.current = r.id);
  FOR i := 0 TO len-1 DO
    Files.WriteChar(r.base.native, buf[i])
  END
END WriteBytes;

PROCEDURE WriteLongReal*(VAR r: Rider; x: LONGREAL);
BEGIN
  ASSERT(r.base.current = r.id);
  IF x = 0.0 THEN
    Files.WriteString(r.base.native, "0")
  ELSE
    Files.WriteLongReal(r.base.native, x)
  END
END WriteLongReal;

PROCEDURE Close*(f: File);
BEGIN
  Files.Close(f.native)
END Close;

PROCEDURE Register*(f: File);
BEGIN
END Register;

PROCEDURE Delete*(name: ARRAY OF CHAR; VAR res: INTEGER);
BEGIN
  res := -1
END Delete;

END MyFiles.

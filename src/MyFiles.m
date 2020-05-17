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

PROCEDURE New*(name: ARRAY OF CHAR): File;
BEGIN
  RETURN NIL
END New;

PROCEDURE Old*(name: ARRAY OF CHAR): File;
BEGIN
  RETURN NIL
END Old;

PROCEDURE Set*(VAR r: Rider; f: File; off: INTEGER);
BEGIN
  ASSERT(off = 0);
  r.base := f;
  r.eof := Files.Eof(f.native);

  stamp := stamp+1;
  r.id := stamp;
  f.current := stamp;
END Set;

PROCEDURE Read*(VAR r: Rider; VAR ch: CHAR);
  VAR f: File;
BEGIN
  f := r.base;
  ASSERT(f.current = r.id);
  Files.ReadChar(f.native, ch);
  r.eof := Files.Eof(f.native)
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
  Files.WriteLongReal(r.base.native, x)
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

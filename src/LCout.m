MODULE LCout; 
(* MODULE to replace Writing System.Log by writing to Disk. *)
IMPORT Linux0, Strings:=Strings0, SYSTEM;

CONST CR = 0DX; NL = 0AX; BLANK = 20X;

stdout=1;

PROCEDURE String*(s : ARRAY OF CHAR);
(* Writes  a String to the Linux console *)
VAR err: LONGINT;
BEGIN
	err:=Linux0.Write0( stdout, SYSTEM.ADR(s[0]), Strings.Length(s));
END String;

PROCEDURE Char*(s : CHAR);
(* Writes  a character to the base of Files.Rider "r" *)
VAR err: LONGINT;
BEGIN
	err:=Linux0.Write0( stdout, SYSTEM.ADR(s), 1);
END Char;

PROCEDURE Ln*();
BEGIN
	Char( CR); Char(NL);
END Ln;

PROCEDURE Int*(value : LONGINT; format : INTEGER);
VAR s : ARRAY 20 OF CHAR; i,j : LONGINT;
BEGIN
	Strings.IntToStr(value,s); j := format-Strings.Length(s);
	IF j < 0 THEN j := 0; END;
	i := 0; WHILE i < j DO Char( BLANK); INC(i) END;
	i:=Linux0.Write0(stdout,SYSTEM.ADR(s[0]),Strings.Length(s));
END Int;

PROCEDURE Test*;
VAR long : LONGINT; i : INTEGER; 
BEGIN
	String ("Das ist ein String"); Ln();
	i := 10; long := 100;
	Int(i,5); Ln(); Int(long,5); Ln();
END Test;

END LCout.

MODULE Strings0;	(** portable *) (* ejz, *)

TYPE LONGINT = INTEGER;

(** Strings is a utility module that provides procedures to manipulate strings.
		Note: All strings MUST be 0X terminated. *)
	VAR
		isAlpha*: ARRAY 256 OF BOOLEAN; (** all letters in the oberon charset *)
		ISOToOberon*, OberonToISO*: ARRAY 256 OF CHAR; (** Translation tables for iso-8859-1 to oberon ascii code. *)

(** Length of str. *)
	PROCEDURE Length*(VAR str(** in *): ARRAY OF CHAR): LONGINT;
		VAR i, l: LONGINT;
	BEGIN
		l := LEN(str); i := 0;
		WHILE (i < l) & (str[i] # 0X) DO
			INC(i)
		END;
		RETURN i
	END Length;

(** Append this to to. *)
	PROCEDURE Append*(VAR to(** in/out *): ARRAY OF CHAR; this: ARRAY OF CHAR);
		VAR i, j, l: LONGINT;
	BEGIN
		i := 0;
		WHILE to[i] # 0X DO
			INC(i)
		END;
		l := LEN(to)-1; j := 0;
		WHILE (i < l) & (this[j] # 0X) DO
			to[i] := this[j]; INC(i); INC(j)
		END;
		to[i] := 0X
	END Append;

(** Append this to to. *)
	PROCEDURE AppendCh*(VAR to(** in/out *): ARRAY OF CHAR; this: CHAR);
		VAR i: LONGINT;
	BEGIN
		i := 0;
		WHILE to[i] # 0X DO
			INC(i)
		END;
		IF i < (LEN(to)-1) THEN
			to[i] := this; to[i+1] := 0X
		END
	END AppendCh;

(** TRUE if ch is a hexadecimal digit. *)
	PROCEDURE IsHexDigit*(ch: CHAR): BOOLEAN;
	BEGIN
		RETURN ((ch >= "0") & (ch <= "9")) OR ((CAP(ch) >= "A") & (CAP(ch) <= "F"))
	END IsHexDigit;

(** TRUE if ch is a decimal digit. *)
	PROCEDURE IsDigit*(ch: CHAR): BOOLEAN;
	BEGIN
		RETURN (ch >= "0") & (ch <= "9")
	END IsDigit;

(** TRUE if ch is a letter. *)
	PROCEDURE IsAlpha*(ch: CHAR): BOOLEAN;
	BEGIN
		RETURN isAlpha[ORD(ch)]
	END IsAlpha;

(** If ch is an upper-case letter return the corresponding lower-case letter. *)
	PROCEDURE LowerCh*(ch: CHAR): CHAR;
	BEGIN
		CASE ch OF
			"A" .. "Z": ch := CHR(ORD(ch)-ORD("A")+ORD("a"))
			|80X: ch := 83X
			|81X: ch := 84X
			|82X: ch := 85X
		ELSE
		END;
		RETURN ch
	END LowerCh;

(** If ch is an lower-case letter return the corresponding upper-case letter. *)
	PROCEDURE UpperCh*(ch: CHAR): CHAR;
	BEGIN
		CASE ch OF
			"a" .. "z": ch := CAP(ch)
			|83X: ch := 80X
			|84X: ch := 81X
			|85X: ch := 82X
			|86X: ch := "A"
			|87X: ch := "E"
			|88X: ch := "I"
			|89X: ch := "O"
			|8AX: ch := "U"
			|8BX: ch := "A"
			|8CX: ch := "E"
			|8DX: ch := "I"
			|8EX: ch := "O"
			|8FX: ch := "U"
			|90X: ch := "E"
			|91X: ch := "E"
			|92X: ch := "I"
			|93X: ch := "C"
			|94X: ch := "A"
			|95X: ch := "N"
			|96X: ch := "S"
		ELSE
		END;
		RETURN ch
	END UpperCh;

(** Convert str to all lower-case letters. *)
	PROCEDURE Lower*(VAR str(** in *), lstr(** out *): ARRAY OF CHAR);
		VAR i: LONGINT;
	BEGIN
		i := 0;
		WHILE str[i] # 0X DO
			lstr[i] := LowerCh(str[i]); INC(i)
		END;
		lstr[i] := 0X
	END Lower;

(** Convert str to all upper-case letters. *)
	PROCEDURE Upper*(VAR str(** in *), ustr(** out *): ARRAY OF CHAR);
		VAR i: LONGINT;
	BEGIN
		i := 0;
		WHILE str[i] # 0X DO
			ustr[i] := UpperCh(str[i]); INC(i)
		END;
		ustr[i] := 0X
	END Upper;

(** Is str prefixed by pre? *)
	PROCEDURE Prefix*(pre: ARRAY OF CHAR; VAR str(** in *): ARRAY OF CHAR): BOOLEAN;
		VAR i: LONGINT;
	BEGIN
		i := 0;
		WHILE (pre[i] # 0X) & (pre[i] = str[i]) DO
			INC(i)
		END;
		RETURN pre[i] = 0X
	END Prefix;

(** Checks if str is prefixed by pre. The case is ignored. *)
	PROCEDURE CAPPrefix*(pre: ARRAY OF CHAR; VAR str(** in *): ARRAY OF CHAR): BOOLEAN;
		VAR i: LONGINT;
	BEGIN
		i := 0;
		WHILE (pre[i] # 0X) & (CAP(pre[i]) = CAP(str[i])) DO
			INC(i)
		END;
		RETURN pre[i] = 0X
	END CAPPrefix;

(** Compare str1 to str2. The case is ignored. *)
	PROCEDURE CAPCompare*(VAR str1(** in *), str2(** in *): ARRAY OF CHAR): BOOLEAN;
		VAR i: LONGINT;
	BEGIN
		i := 0;
		WHILE (str1[i] # 0X) & (str2[i] # 0X) & (CAP(str1[i]) = CAP(str2[i])) DO
			INC(i)
		END;
		RETURN str1[i] = str2[i]
	END CAPCompare;

(** Get the parameter-value on line. The parameter value is started behind the first colon character. *)
	PROCEDURE GetPar*(VAR line(** in *), par(** out *): ARRAY OF CHAR);
		VAR i, j, l: LONGINT;
	BEGIN
		i := 0;
		WHILE (line[i] # 0X) & (line[i] # ":") DO
			INC(i)
		END;
		IF line[i] = ":" THEN
			INC(i)
		END;
		WHILE (line[i] # 0X) & (line[i] <= " ") DO
			INC(i)
		END;
		l := LEN(par)-1; j := 0;
		WHILE (j < l) & (line[i] # 0X) DO
			par[j] := line[i]; INC(j); INC(i)
		END;
		par[j] := 0X
	END GetPar;

(** Get the suffix of str. The suffix is started by the last dot in str. *)
	PROCEDURE GetSuffix*(VAR str(** in *), suf(** out *): ARRAY OF CHAR);
		VAR i, j, l, dot: LONGINT;
	BEGIN
		dot := -1; i := 0;
		WHILE str[i] # 0X DO
			IF str[i] = "." THEN
				dot := i
			ELSIF str[i] = "/" THEN
				dot := -1
			END;
			INC(i)
		END;
		j := 0;
		IF dot > 0 THEN
			l := LEN(suf)-1; i := dot+1;
			WHILE (j < l) & (str[i] # 0X) DO
				suf[j] := str[i]; INC(j); INC(i)
			END
		END;
		suf[j] := 0X
	END GetSuffix;

(** Change the suffix of str to suf. *)
	PROCEDURE ChangeSuffix*(VAR str(** in/out *): ARRAY OF CHAR; suf: ARRAY OF CHAR);
		VAR i, j, l, dot: LONGINT;
	BEGIN
		dot := -1; i := 0;
		WHILE str[i] # 0X DO
			IF str[i] = "." THEN
				dot := i
			ELSIF str[i] = "/" THEN
				dot := -1
			END;
			INC(i)
		END;
		IF dot > 0 THEN
			l := LEN(str)-1; i := dot+1; j := 0;
			WHILE (i < l) & (suf[j] # 0X) DO
				str[i] := suf[j]; INC(i); INC(j)
			END;
			str[i] := 0X
		END
	END ChangeSuffix;

(** Search in src starting at pos for the next occurrence of pat.  Returns pos=-1 if not found. *)
	PROCEDURE Search*(pat: ARRAY OF CHAR; VAR src(** in *): ARRAY OF CHAR; VAR pos(** in/out *): LONGINT);
		CONST MaxPat = 128;
		VAR
			buf: ARRAY MaxPat OF CHAR;
			len, i, srclen: LONGINT;
		PROCEDURE Find(beg: LONGINT);
			VAR
				i, j, b, e: LONGINT;
				ch: CHAR;
				ref: ARRAY MaxPat OF CHAR;
		BEGIN
			ch := src[pos]; INC(pos);
			ref[0] := ch;
			i := 0; j := 0; b := 0; e := 1;
			WHILE (pos <= srclen) & (i < len) DO
				IF buf[i] = ch THEN
					INC(i); j := (j + 1) MOD MaxPat
				ELSE
					i := 0; b := (b + 1) MOD MaxPat; j := b
				END;
				IF j # e THEN
					ch := ref[j]
				ELSE
					IF pos >= srclen THEN
						ch := 0X
					ELSE
						ch := src[pos]
					END;
					INC(pos); ref[j] := ch; e := (e + 1) MOD MaxPat; INC(beg);
				END
			END;
			IF i = len THEN
				pos := beg-len
			ELSE
				pos := -1
			END
		END Find;
	BEGIN
		len := Length(pat);
		IF MaxPat < len THEN
			len := MaxPat
		END;
		IF len <= 0 THEN
			pos := -1;
			RETURN
		END;
		i := 0;
		REPEAT
			buf[i] := pat[i]; INC(i)
		UNTIL i >= len;
		srclen := Length(src);
		IF pos < 0 THEN
			pos := 0
		ELSIF pos >= srclen THEN
			pos := -1;
			RETURN
		END;
		Find(pos)
	END Search;

(** Search in src starting at pos for the next occurrence of pat. *)
	PROCEDURE CAPSearch*(pat: ARRAY OF CHAR; VAR src(** in *): ARRAY OF CHAR; VAR pos(** in/out *): LONGINT);
		CONST MaxPat = 128;
		VAR
			buf: ARRAY MaxPat OF CHAR;
			len, i, srclen: LONGINT;
		PROCEDURE Find(beg: LONGINT);
			VAR
				i, j, b, e: LONGINT;
				ch: CHAR;
				ref: ARRAY MaxPat OF CHAR;
		BEGIN
			ch := UpperCh(src[pos]); INC(pos);
			ref[0] := ch;
			i := 0; j := 0; b := 0; e := 1;
			WHILE (pos <= srclen) & (i < len) DO
				IF buf[i] = ch THEN
					INC(i); j := (j + 1) MOD MaxPat
				ELSE
					i := 0; b := (b + 1) MOD MaxPat; j := b
				END;
				IF j # e THEN
					ch := ref[j]
				ELSE
					IF pos >= srclen THEN
						ch := 0X
					ELSE
						ch := UpperCh(src[pos])
					END;
					INC(pos); ref[j] := ch; e := (e + 1) MOD MaxPat; INC(beg);
				END
			END;
			IF i = len THEN
				pos := beg-len
			ELSE
				pos := -1
			END
		END Find;
	BEGIN
		len := Length(pat);
		IF MaxPat < len THEN
			len := MaxPat
		END;
		IF len <= 0 THEN
			pos := -1;
			RETURN
		END;
		i := 0;
		REPEAT
			buf[i] := UpperCh(pat[i]); INC(i)
		UNTIL i >= len;
		srclen := Length(src);
		IF pos < 0 THEN
			pos := 0
		ELSIF pos >= srclen THEN
			pos := -1;
			RETURN
		END;
		Find(pos)
	END CAPSearch;

(** Convert a string into an integer. Leading white space characters are ignored. *)
	PROCEDURE StrToInt*(VAR str: ARRAY OF CHAR; VAR val: LONGINT);
		VAR i, d: LONGINT; ch: CHAR; neg: BOOLEAN;
	BEGIN
		i := 0; ch := str[0];
		WHILE (ch # 0X) & (ch <= " ") DO
			INC(i); ch := str[i]
		END;
		neg := FALSE; IF ch = "+" THEN INC(i); ch := str[i] END;
		IF ch = "-" THEN neg := TRUE; INC(i); ch := str[i] END;
		WHILE (ch # 0X) & (ch <= " ") DO
			INC(i); ch := str[i]
		END;
		val := 0;
		WHILE (ch >= "0") & (ch <= "9") DO
			d := ORD(ch)-ORD("0");
			INC(i); ch := str[i];
			IF val <= ((MAX(LONGINT)-d) DIV 10) THEN
				val := 10*val+d
			ELSIF neg & (val = 214748364) & (d = 8) & ((ch < "0") OR (ch > "9")) THEN
				val := MIN(LONGINT); neg := FALSE
			ELSE
				HALT(99)
			END
		END;
		IF neg THEN val := -val END
	END StrToInt;

(** Convert the substring beginning at position i in str into an integer. Any leading whitespace characters are ignored.
	After the conversion i pointes to the first character after the integer. *)
	PROCEDURE StrToIntPos*(VAR str: ARRAY OF CHAR; VAR val: LONGINT; VAR i: INTEGER);
		VAR noStr: ARRAY 16 OF CHAR;
	BEGIN
		WHILE (str[i] # 0X) & (str[i] <= " ") DO
			INC(i)
		END;
		val := 0;
		IF str[i] = "-" THEN
			noStr[val] := str[i]; INC(val); INC(i);
			WHILE (str[i] # 0X) & (str[i] <= " ") DO
				INC(i)
			END
		END;
		WHILE (str[i] >= "0") & (str[i] <= "9") DO
			noStr[val] := str[i]; INC(val); INC(i)
		END;
		noStr[val] := 0X;
		StrToInt(noStr, val)
	END StrToIntPos;

(** Convert an integer into a string. *)
	PROCEDURE IntToStr*(val: LONGINT; VAR str: ARRAY OF CHAR);
		VAR
			i, j: LONGINT;
			digits: ARRAY 16 OF LONGINT;
	BEGIN
		IF val = MIN(LONGINT) THEN
			COPY("-2147483648", str);
			RETURN
		END;
		IF val < 0 THEN
			val := -val; str[0] := "-"; j := 1
		ELSE
			j := 0
		END;
		i := 0;
		REPEAT
			digits[i] := val MOD 10; INC(i); val := val DIV 10
		UNTIL val = 0;
		DEC(i);
		WHILE i >= 0 DO
			str[j] := CHR(digits[i]+ORD("0")); INC(j); DEC(i)
		END;
		str[j] := 0X
	END IntToStr;

(** Convert a string into a boolean. "Yes", "True" and "On" are TRUE all other strings are FALSE.
	Leading white space characters are ignored. *)
	PROCEDURE StrToBool*(VAR str: ARRAY OF CHAR; VAR b: BOOLEAN);
		VAR i: LONGINT;
	BEGIN
		i := 0;
		WHILE (str[i] # 0X) & (str[i] <= " ") DO
			INC(i)
		END;
		CASE CAP(str[i]) OF
			"Y", "T": b := TRUE
			|"O": b := CAP(str[i+1]) = "N"
		ELSE
			b := FALSE
		END
	END StrToBool;

(** Convert a boolean into "Yes" or "No". *)
	PROCEDURE BoolToStr*(b: BOOLEAN; VAR str: ARRAY OF CHAR);
	BEGIN
		IF b THEN
			COPY("Yes", str)
		ELSE
			COPY("No", str)
		END
	END BoolToStr;

(** Convert a string to a set *)
	PROCEDURE StrToSet* (str: ARRAY OF CHAR; VAR set: SET);
	VAR i, d, d1: INTEGER; ch: CHAR; dot: BOOLEAN;
	BEGIN
		set := {}; dot := FALSE;
		i := 0; ch := str[i];
		WHILE (ch # 0X) & (ch # "}") DO
			WHILE (ch # 0X) & ((ch < "0") OR (ch > "9")) DO INC(i); ch := str[i] END;
			d := 0; WHILE (ch >= "0") & (ch <= "9") DO d := d*10 + ORD(ch) - 30H; INC(i); ch := str[i] END;
			IF d <= MAX(SET) THEN INCL(set, d) END;
			IF dot THEN
				d1 := 0;
				WHILE (d1 <= MAX(SET)) & (d1 < d) DO INCL(set, d1); INC(d1) END;
				dot := FALSE
			END;
			WHILE ch = " " DO INC(i); ch := str[i] END;
			IF ch = "." THEN d1 := d + 1; dot := TRUE END
		END
	END StrToSet;

(** Convert a set to a string *)
	PROCEDURE SetToStr* (set: SET; VAR str: ARRAY OF CHAR);
	VAR i, j, k: INTEGER; noFirst: BOOLEAN;
	BEGIN
		str[0] := "{"; i := 0; k := 1; noFirst := FALSE;
		WHILE i <= MAX(SET) DO
			IF i IN set THEN
				IF noFirst THEN str[k] := ","; INC(k) ELSE noFirst := TRUE END;
				IF i >= 10 THEN str[k] := CHR(i DIV 10 + 30H); INC(k) END;
				str[k] := CHR(i MOD 10 + 30H); INC(k);
				j := i; INC(i);
				WHILE (i <= MAX(SET)) & (i IN set) DO INC(i) END;
				IF i-2 > j THEN
					str[k] := "."; str[k+1] := "."; INC(k, 2); j := i - 1;
					IF j >= 10 THEN str[k] := CHR(j DIV 10 + 30H); INC(k) END;
					str[k] := CHR(j MOD 10 + 30H); INC(k)
				ELSE i := j
				END
			END;
			INC(i)
		END;
		str[k] := "}"; str[k+1] := 0X
	END SetToStr;

	PROCEDURE Init();
		VAR i: LONGINT; 
	BEGIN
	
		FOR i := 0 TO 255 DO
			isAlpha[i] := ((i >= ORD("A")) & (i <= ORD("Z"))) OR ((i >= ORD("a")) & (i <= ORD("z")))
		END;
		isAlpha[ORD(80X)] := TRUE; isAlpha[ORD(81X)] := TRUE; isAlpha[ORD(82X)] := TRUE;
		isAlpha[ORD(83X)] := TRUE; isAlpha[ORD(84X)] := TRUE; isAlpha[ORD(85X)] := TRUE;
		isAlpha[ORD(86X)] := TRUE; isAlpha[ORD(87X)] := TRUE; isAlpha[ORD(88X)] := TRUE;
		isAlpha[ORD(89X)] := TRUE; isAlpha[ORD(8AX)] := TRUE; isAlpha[ORD(8BX)] := TRUE;
		isAlpha[ORD(8CX)] := TRUE; isAlpha[ORD(8DX)] := TRUE; isAlpha[ORD(8EX)] := TRUE;
		isAlpha[ORD(8FX)] := TRUE; isAlpha[ORD(90X)] := TRUE; isAlpha[ORD(91X)] := TRUE;
		isAlpha[ORD(92X)] := TRUE; isAlpha[ORD(93X)] := TRUE; isAlpha[ORD(94X)] := TRUE;
		isAlpha[ORD(95X)] := TRUE; isAlpha[ORD(96X)] := TRUE;
		FOR i := 0 TO 255 DO
			ISOToOberon[i] := CHR(i); OberonToISO[i] := CHR(i)
		END;
		ISOToOberon[8] := 7FX;
		ISOToOberon[146] := 27X;
		ISOToOberon[160] := 20X;
		ISOToOberon[162] := 63X;
		ISOToOberon[166] := 7CX;
		ISOToOberon[168] := 22X;
		ISOToOberon[169] := 63X;
		ISOToOberon[170] := 61X;
		ISOToOberon[171] := 3CX;
		ISOToOberon[173] := 2DX;
		ISOToOberon[174] := 72X;
		ISOToOberon[175] := 2DX;
		ISOToOberon[176] := 6FX;
		ISOToOberon[178] := 32X;
		ISOToOberon[179] := 33X;
		ISOToOberon[180] := 27X;
		ISOToOberon[183] := 2EX;
		ISOToOberon[185] := 31X;
		ISOToOberon[186] := 30X;
		ISOToOberon[187] := 3EX;
		ISOToOberon[192] := 41X;
		ISOToOberon[193] := 41X;
		ISOToOberon[194] := 41X;
		ISOToOberon[195] := 41X;
		ISOToOberon[196] := 80X; OberonToISO[128] := 0C4X;
		ISOToOberon[197] := 41X;
		ISOToOberon[198] := 41X;
		ISOToOberon[199] := 43X;
		ISOToOberon[200] := 45X;
		ISOToOberon[201] := 45X;
		ISOToOberon[202] := 45X;
		ISOToOberon[203] := 45X;
		ISOToOberon[204] := 49X;
		ISOToOberon[205] := 49X;
		ISOToOberon[206] := 49X;
		ISOToOberon[207] := 49X;
		ISOToOberon[208] := 44X;
		ISOToOberon[209] := 4EX;
		ISOToOberon[210] := 4FX;
		ISOToOberon[211] := 4FX;
		ISOToOberon[212] := 4FX;
		ISOToOberon[213] := 4FX;
		ISOToOberon[214] := 81X; OberonToISO[129] := 0D6X;
		ISOToOberon[215] := 2AX;
		ISOToOberon[216] := 4FX;
		ISOToOberon[217] := 55X;
		ISOToOberon[218] := 55X;
		ISOToOberon[219] := 55X;
		ISOToOberon[220] := 82X; OberonToISO[130] := 0DCX;
		ISOToOberon[221] := 59X;
		ISOToOberon[222] := 50X;
		ISOToOberon[223] := 96X; OberonToISO[150] := 0DFX;
		ISOToOberon[224] := 8BX; OberonToISO[139] := 0E0X;
		ISOToOberon[225] := 94X; OberonToISO[148] := 0E1X;
		ISOToOberon[226] := 86X; OberonToISO[134] := 0E2X;
		ISOToOberon[227] := 61X;
		ISOToOberon[228] := 83X; OberonToISO[131] := 0E4X;
		ISOToOberon[229] := 61X;
		ISOToOberon[230] := 61X;
		ISOToOberon[231] := 93X; OberonToISO[147] := 0E7X;
		ISOToOberon[232] := 8CX; OberonToISO[140] := 0E8X;
		ISOToOberon[233] := 90X; OberonToISO[144] := 0E9X;
		ISOToOberon[234] := 87X; OberonToISO[135] := 0EAX;
		ISOToOberon[235] := 91X; OberonToISO[145] := 0EBX;
		ISOToOberon[236] := 8DX; OberonToISO[141] := 0ECX;
		ISOToOberon[237] := 69X;
		ISOToOberon[238] := 88X; OberonToISO[136] := 0EEX;
		ISOToOberon[239] := 92X; OberonToISO[146] := 0EFX;
		ISOToOberon[240] := 64X;
		ISOToOberon[241] := 95X; OberonToISO[149] := 0F1X;
		ISOToOberon[242] := 8EX; OberonToISO[142] := 0F2X;
		ISOToOberon[243] := 6FX;
		ISOToOberon[244] := 89X; OberonToISO[137] := 0F4X;
		ISOToOberon[245] := 6FX;
		ISOToOberon[246] := 84X; OberonToISO[132] := 0F6X;
		ISOToOberon[248] := 6FX;
		ISOToOberon[249] := 8FX; OberonToISO[143] := 0F9X;
		ISOToOberon[250] := 75X;
		ISOToOberon[251] := 8AX; OberonToISO[138] := 0FBX;
		ISOToOberon[252] := 85X; OberonToISO[133] := 0FCX;
		ISOToOberon[253] := 79X;
		ISOToOberon[254] := 70X;
		ISOToOberon[255] := 79X;
	END Init;

BEGIN
	Init()
END Strings0.


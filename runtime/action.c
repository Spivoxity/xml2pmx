/* action.c -- Copyright (c) 2020 J. M. Spivey */

          ACTION(PUSH_x1)
          ALSO(PUSH_x1+1)
          ALSO(PUSH_x1+2)
          ALSO(PUSH_x1+3)
          ALSO(PUSH_x1+4)
          ALSO(PUSH_x1+5)
          ALSO(PUSH_x1+6)
          ALSO(PUSH_x1+7)
          ALSO(PUSH_x1+8)
          ALSO(PUSH_x1+9)
          ALSO(PUSH_x1+10)
          ALSO(PUSH_x1+11)
               pc = pc0 + 1;
               sp--; sp[0].i =  ir-2 ;
               NEXT;

          ACTION(PUSH_1)
               pc = pc0 + 2;
               sp--; sp[0].i =  get1(pc0+1) ;
               NEXT;

          ACTION(PUSH_2)
               pc = pc0 + 3;
               sp--; sp[0].i =  get2(pc0+1) ;
               NEXT;

          ACTION(LDKW_1)
               pc = pc0 + 2;
               sp--; sp[0].i =  konst(get1(pc0+1)).i ;
               NEXT;

          ACTION(LDKW_2)
               pc = pc0 + 3;
               sp--; sp[0].i =  konst(get2(pc0+1)).i ;
               NEXT;

          ACTION(LDKF_1)
               pc = pc0 + 2;
               sp--; sp[0].f =  konst(get1(pc0+1)).f ;
               NEXT;

          ACTION(LDKF_2)
               pc = pc0 + 3;
               sp--; sp[0].f =  konst(get2(pc0+1)).f ;
               NEXT;

          ACTION(LOCAL_x1)
               pc = pc0 + 1;
               sp--; sp[0].a = address( local(0) );
               NEXT;

          ACTION(LOCAL_1)
               pc = pc0 + 2;
               sp--; sp[0].a = address( local(get1(pc0+1)) );
               NEXT;

          ACTION(LOCAL_2)
               pc = pc0 + 3;
               sp--; sp[0].a = address( local(get2(pc0+1)) );
               NEXT;

          ACTION(OFFSET)
               pc = pc0 + 1;
               sp[1].a = address( pointer(sp[1]) + sp[0].i ); sp++;
               NEXT;

          ACTION(INDEXS)
               pc = pc0 + 1;
               sp[1].a = address( index(sp[1], sp[0], 1) ); sp++;
               NEXT;

          ACTION(INDEXW)
               pc = pc0 + 1;
               sp[1].a = address( index(sp[1], sp[0], 2) ); sp++;
               NEXT;

          ACTION(INDEXD)
               pc = pc0 + 1;
               sp[1].a = address( index(sp[1], sp[0], 3) ); sp++;
               NEXT;

          ACTION(LOADW)
               pc = pc0 + 1;
               sp[0].i =  load(sp[0], int) ;
               NEXT;

          ACTION(LOADS)
               pc = pc0 + 1;
               sp[0].i =  load(sp[0], short) ;
               NEXT;

          ACTION(LOADC)
               pc = pc0 + 1;
               sp[0].i =  load(sp[0], uchar) ;
               NEXT;

          ACTION(LOADF)
               pc = pc0 + 1;
               sp[0].f =  load(sp[0], float) ;
               NEXT;

          ACTION(STOREW)
               pc = pc0 + 1;
               {  store(sp[1].i, sp[0], int) ; } sp += 2;
               NEXT;

          ACTION(STORES)
               pc = pc0 + 1;
               {  store(sp[1].i, sp[0], short) ; } sp += 2;
               NEXT;

          ACTION(STOREC)
               pc = pc0 + 1;
               {  store(sp[1].i, sp[0], uchar) ; } sp += 2;
               NEXT;

          ACTION(STOREF)
               pc = pc0 + 1;
               {  store(sp[1].f, sp[0], float) ; } sp += 2;
               NEXT;

          ACTION(LDLW_x1)
          ALSO(LDLW_x1+1)
          ALSO(LDLW_x1+2)
          ALSO(LDLW_x1+3)
          ALSO(LDLW_x1+4)
          ALSO(LDLW_x1+5)
               pc = pc0 + 1;
               sp--; sp[0].i =  ldl(ir*4-160, int);
               NEXT;

          ACTION(LDLW_x2)
          ALSO(LDLW_x2+1)
          ALSO(LDLW_x2+2)
          ALSO(LDLW_x2+3)
          ALSO(LDLW_x2+4)
          ALSO(LDLW_x2+5)
               pc = pc0 + 1;
               sp--; sp[0].i =  ldl(ir*4-148, int);
               NEXT;

          ACTION(LDLW_1)
               pc = pc0 + 2;
               sp--; sp[0].i =  ldl(get1(pc0+1), int);
               NEXT;

          ACTION(LDLW_2)
               pc = pc0 + 3;
               sp--; sp[0].i =  ldl(get2(pc0+1), int);
               NEXT;

          ACTION(LDLS_1)
               pc = pc0 + 2;
               sp--; sp[0].i =  ldl(get1(pc0+1), short) ;
               NEXT;

          ACTION(LDLS_2)
               pc = pc0 + 3;
               sp--; sp[0].i =  ldl(get2(pc0+1), short) ;
               NEXT;

          ACTION(LDLC_1)
               pc = pc0 + 2;
               sp--; sp[0].i =  ldl(get1(pc0+1), uchar) ;
               NEXT;

          ACTION(LDLC_2)
               pc = pc0 + 3;
               sp--; sp[0].i =  ldl(get2(pc0+1), uchar) ;
               NEXT;

          ACTION(LDLF_1)
               pc = pc0 + 2;
               sp--; sp[0].f =  ldl(get1(pc0+1), float) ;
               NEXT;

          ACTION(LDLF_2)
               pc = pc0 + 3;
               sp--; sp[0].f =  ldl(get2(pc0+1), float) ;
               NEXT;

          ACTION(STLW_x1)
          ALSO(STLW_x1+1)
          ALSO(STLW_x1+2)
          ALSO(STLW_x1+3)
          ALSO(STLW_x1+4)
          ALSO(STLW_x1+5)
               pc = pc0 + 1;
               {  stl(ir*4-240, sp[0].i, int) ; } sp += 1;
               NEXT;

          ACTION(STLW_x2)
          ALSO(STLW_x2+1)
          ALSO(STLW_x2+2)
          ALSO(STLW_x2+3)
          ALSO(STLW_x2+4)
          ALSO(STLW_x2+5)
               pc = pc0 + 1;
               {  stl(ir*4-228, sp[0].i, int) ; } sp += 1;
               NEXT;

          ACTION(STLW_1)
               pc = pc0 + 2;
               {  stl(get1(pc0+1), sp[0].i, int) ; } sp += 1;
               NEXT;

          ACTION(STLW_2)
               pc = pc0 + 3;
               {  stl(get2(pc0+1), sp[0].i, int) ; } sp += 1;
               NEXT;

          ACTION(STLS_1)
               pc = pc0 + 2;
               {  stl(get1(pc0+1), sp[0].i, short) ; } sp += 1;
               NEXT;

          ACTION(STLS_2)
               pc = pc0 + 3;
               {  stl(get2(pc0+1), sp[0].i, short) ; } sp += 1;
               NEXT;

          ACTION(STLC_1)
               pc = pc0 + 2;
               {  stl(get1(pc0+1), sp[0].i, uchar) ; } sp += 1;
               NEXT;

          ACTION(STLC_2)
               pc = pc0 + 3;
               {  stl(get2(pc0+1), sp[0].i, uchar) ; } sp += 1;
               NEXT;

          ACTION(STLF_1)
               pc = pc0 + 2;
               {  stl(get1(pc0+1), sp[0].f, float) ; } sp += 1;
               NEXT;

          ACTION(STLF_2)
               pc = pc0 + 3;
               {  stl(get2(pc0+1), sp[0].f, float) ; } sp += 1;
               NEXT;

          ACTION(LDGW_K)
               pc = pc0 + 2;
               sp--; sp[0].i =  ldg(get1(pc0+1), int) ;
               NEXT;

          ACTION(LDGW_L)
               pc = pc0 + 3;
               sp--; sp[0].i =  ldg(get2(pc0+1), int) ;
               NEXT;

          ACTION(LDGS_K)
               pc = pc0 + 2;
               sp--; sp[0].i =  ldg(get1(pc0+1), short) ;
               NEXT;

          ACTION(LDGS_L)
               pc = pc0 + 3;
               sp--; sp[0].i =  ldg(get2(pc0+1), short) ;
               NEXT;

          ACTION(LDGC_K)
               pc = pc0 + 2;
               sp--; sp[0].i =  ldg(get1(pc0+1), uchar) ;
               NEXT;

          ACTION(LDGC_L)
               pc = pc0 + 3;
               sp--; sp[0].i =  ldg(get2(pc0+1), uchar) ;
               NEXT;

          ACTION(LDGF_K)
               pc = pc0 + 2;
               sp--; sp[0].f =  ldg(get1(pc0+1), float) ;
               NEXT;

          ACTION(LDGF_L)
               pc = pc0 + 3;
               sp--; sp[0].f =  ldg(get2(pc0+1), float) ;
               NEXT;

          ACTION(STGW_K)
               pc = pc0 + 2;
               {  stg(get1(pc0+1), sp[0].i, int) ; } sp += 1;
               NEXT;

          ACTION(STGW_L)
               pc = pc0 + 3;
               {  stg(get2(pc0+1), sp[0].i, int) ; } sp += 1;
               NEXT;

          ACTION(STGS_K)
               pc = pc0 + 2;
               {  stg(get1(pc0+1), sp[0].i, short) ; } sp += 1;
               NEXT;

          ACTION(STGS_L)
               pc = pc0 + 3;
               {  stg(get2(pc0+1), sp[0].i, short) ; } sp += 1;
               NEXT;

          ACTION(STGC_K)
               pc = pc0 + 2;
               {  stg(get1(pc0+1), sp[0].i, uchar) ; } sp += 1;
               NEXT;

          ACTION(STGC_L)
               pc = pc0 + 3;
               {  stg(get2(pc0+1), sp[0].i, uchar) ; } sp += 1;
               NEXT;

          ACTION(STGF_K)
               pc = pc0 + 2;
               {  stg(get1(pc0+1), sp[0].f, float) ; } sp += 1;
               NEXT;

          ACTION(STGF_L)
               pc = pc0 + 3;
               {  stg(get2(pc0+1), sp[0].f, float) ; } sp += 1;
               NEXT;

          ACTION(LDNW_x1)
          ALSO(LDNW_x1+1)
          ALSO(LDNW_x1+2)
          ALSO(LDNW_x1+3)
          ALSO(LDNW_x1+4)
          ALSO(LDNW_x1+5)
          ALSO(LDNW_x1+6)
          ALSO(LDNW_x1+7)
          ALSO(LDNW_x1+8)
          ALSO(LDNW_x1+9)
          ALSO(LDNW_x1+10)
          ALSO(LDNW_x1+11)
          ALSO(LDNW_x1+12)
               pc = pc0 + 1;
               sp[0].i =  ldn(ir*4-376, sp[0]) ;
               NEXT;

          ACTION(LDNW_1)
               pc = pc0 + 2;
               sp[0].i =  ldn(get1(pc0+1), sp[0]) ;
               NEXT;

          ACTION(LDNW_2)
               pc = pc0 + 3;
               sp[0].i =  ldn(get2(pc0+1), sp[0]) ;
               NEXT;

          ACTION(STNW_x1)
          ALSO(STNW_x1+1)
          ALSO(STNW_x1+2)
          ALSO(STNW_x1+3)
          ALSO(STNW_x1+4)
          ALSO(STNW_x1+5)
          ALSO(STNW_x1+6)
          ALSO(STNW_x1+7)
          ALSO(STNW_x1+8)
          ALSO(STNW_x1+9)
          ALSO(STNW_x1+10)
          ALSO(STNW_x1+11)
          ALSO(STNW_x1+12)
               pc = pc0 + 1;
               {  stn(ir*4-436, sp[1].i, sp[0]) ; } sp += 2;
               NEXT;

          ACTION(STNW_1)
               pc = pc0 + 2;
               {  stn(get1(pc0+1), sp[1].i, sp[0]) ; } sp += 2;
               NEXT;

          ACTION(STNW_2)
               pc = pc0 + 3;
               {  stn(get2(pc0+1), sp[1].i, sp[0]) ; } sp += 2;
               NEXT;

          ACTION(LDIW)
               pc = pc0 + 1;
               sp[1].i =  ldi(sp[1], sp[0], int) ; sp++;
               NEXT;

          ACTION(LDIS)
               pc = pc0 + 1;
               sp[1].i =  ldi(sp[1], sp[0], short) ; sp++;
               NEXT;

          ACTION(LDIC)
               pc = pc0 + 1;
               sp[1].i =  ldi(sp[1], sp[0], uchar) ; sp++;
               NEXT;

          ACTION(LDIF)
               pc = pc0 + 1;
               sp[1].f =  ldi(sp[1], sp[0], float) ; sp++;
               NEXT;

          ACTION(STIW)
               pc = pc0 + 1;
               {  sti(sp[2].i, sp[1], sp[0], int) ; } sp += 3;
               NEXT;

          ACTION(STIS)
               pc = pc0 + 1;
               {  sti(sp[2].i, sp[1], sp[0], short) ; } sp += 3;
               NEXT;

          ACTION(STIC)
               pc = pc0 + 1;
               {  sti(sp[2].i, sp[1], sp[0], uchar) ; } sp += 3;
               NEXT;

          ACTION(STIF)
               pc = pc0 + 1;
               {  sti(sp[2].f, sp[1], sp[0], float) ; } sp += 3;
               NEXT;

          ACTION(LOADD)
               pc = pc0 + 1;
               sp--; putdbl(&sp[0],  getdbl(valptr(sp[1])) );
               NEXT;

          ACTION(STORED)
               pc = pc0 + 1;
               {  putdbl(valptr(sp[0]), getdbl(&sp[1])) ; } sp += 3;
               NEXT;

          ACTION(LDKD_1)
               pc = pc0 + 2;
               sp -= 2; putdbl(&sp[0],  getdbl(&konst(get1(pc0+1))) );
               NEXT;

          ACTION(LDKD_2)
               pc = pc0 + 3;
               sp -= 2; putdbl(&sp[0],  getdbl(&konst(get2(pc0+1))) );
               NEXT;

          ACTION(LOADQ)
               pc = pc0 + 1;
               sp--; putlong(&sp[0],  getlong(valptr(sp[1])) );
               NEXT;

          ACTION(STOREQ)
               pc = pc0 + 1;
               {  putlong(valptr(sp[0]), getlong(&sp[1])) ; } sp += 3;
               NEXT;

          ACTION(LDKQ_1)
               pc = pc0 + 2;
               sp -= 2; putlong(&sp[0],  getlong(&konst(get1(pc0+1))) );
               NEXT;

          ACTION(LDKQ_2)
               pc = pc0 + 3;
               sp -= 2; putlong(&sp[0],  getlong(&konst(get2(pc0+1))) );
               NEXT;

          ACTION(INCL_1)
               pc = pc0 + 2;
               {  indir(local(get1(pc0+1)), int)++ ; }
               NEXT;

          ACTION(DECL_1)
               pc = pc0 + 2;
               { indir(local(get1(pc0+1)), int)--; }
               NEXT;

          ACTION(DUP)
          ALSO(DUP+1)
          ALSO(DUP+2)
               pc = pc0 + 1;
               { dup(ir-138, sp); }
               NEXT;

          ACTION(SWAP)
               pc = pc0 + 1;
               { swap(sp); }
               NEXT;

          ACTION(POP_1)
               pc = pc0 + 2;
               { sp += get1(pc0+1); }
               NEXT;

          ACTION(PLUS)
               pc = pc0 + 1;
               sp[1].i =  sp[1].i + sp[0].i ; sp++;
               NEXT;

          ACTION(MINUS)
               pc = pc0 + 1;
               sp[1].i =  sp[1].i - sp[0].i ; sp++;
               NEXT;

          ACTION(TIMES)
               pc = pc0 + 1;
               sp[1].i =  sp[1].i * sp[0].i ; sp++;
               NEXT;

          ACTION(UMINUS)
               pc = pc0 + 1;
               sp[0].i =  - sp[0].i ;
               NEXT;

          ACTION(AND)
               pc = pc0 + 1;
               sp[1].i =  sp[1].i && sp[0].i ; sp++;
               NEXT;

          ACTION(OR)
               pc = pc0 + 1;
               sp[1].i =  sp[1].i || sp[0].i ; sp++;
               NEXT;

          ACTION(NOT)
               pc = pc0 + 1;
               sp[0].i =  ! sp[0].i ;
               NEXT;

          ACTION(INC)
               pc = pc0 + 1;
               sp[0].i =  sp[0].i + 1 ;
               NEXT;

          ACTION(DEC)
               pc = pc0 + 1;
               sp[0].i =  sp[0].i - 1 ;
               NEXT;

          ACTION(BITAND)
               pc = pc0 + 1;
               sp[1].i =  sp[1].i & sp[0].i ; sp++;
               NEXT;

          ACTION(BITOR)
               pc = pc0 + 1;
               sp[1].i =  sp[1].i | sp[0].i ; sp++;
               NEXT;

          ACTION(BITXOR)
               pc = pc0 + 1;
               sp[1].i =  sp[1].i ^ sp[0].i ; sp++;
               NEXT;

          ACTION(BITNOT)
               pc = pc0 + 1;
               sp[0].i =  ~ sp[0].i ;
               NEXT;

          ACTION(LSL)
               pc = pc0 + 1;
               sp[1].i =  sp[1].i << sp[0].i ; sp++;
               NEXT;

          ACTION(LSR)
               pc = pc0 + 1;
               sp[1].i =  (unsigned) sp[1].i>>sp[0].i ; sp++;
               NEXT;

          ACTION(ASR)
               pc = pc0 + 1;
               sp[1].i =  sp[1].i >> sp[0].i ; sp++;
               NEXT;

          ACTION(ROR)
               pc = pc0 + 1;
               sp[1].i =  ror(sp[1].i, sp[0].i) ; sp++;
               NEXT;

          ACTION(DIV)
               pc = pc0 + 1;
               {  int_div(sp) ; } sp++;
               NEXT;

          ACTION(MOD)
               pc = pc0 + 1;
               {  int_mod(sp) ; } sp++;
               NEXT;

          ACTION(EQ)
               pc = pc0 + 1;
               sp[1].i =  sp[1].i == sp[0].i ; sp++;
               NEXT;

          ACTION(LT)
               pc = pc0 + 1;
               sp[1].i =  sp[1].i < sp[0].i ; sp++;
               NEXT;

          ACTION(GT)
               pc = pc0 + 1;
               sp[1].i =  sp[1].i > sp[0].i ; sp++;
               NEXT;

          ACTION(LEQ)
               pc = pc0 + 1;
               sp[1].i =  sp[1].i <= sp[0].i ; sp++;
               NEXT;

          ACTION(GEQ)
               pc = pc0 + 1;
               sp[1].i =  sp[1].i >= sp[0].i ; sp++;
               NEXT;

          ACTION(NEQ)
               pc = pc0 + 1;
               sp[1].i =  sp[1].i != sp[0].i ; sp++;
               NEXT;

          ACTION(JEQ_S)
               pc = pc0 + 2;
               {  if (sp[1].i == sp[0].i) jump(get1(pc0+1)) ; } sp += 2;
               NEXT;

          ACTION(JEQ_R)
               pc = pc0 + 3;
               {  if (sp[1].i == sp[0].i) jump(get2(pc0+1)) ; } sp += 2;
               NEXT;

          ACTION(JLT_S)
               pc = pc0 + 2;
               {  if (sp[1].i < sp[0].i) jump(get1(pc0+1)) ; } sp += 2;
               NEXT;

          ACTION(JLT_R)
               pc = pc0 + 3;
               {  if (sp[1].i < sp[0].i) jump(get2(pc0+1)) ; } sp += 2;
               NEXT;

          ACTION(JGT_S)
               pc = pc0 + 2;
               {  if (sp[1].i > sp[0].i) jump(get1(pc0+1)) ; } sp += 2;
               NEXT;

          ACTION(JGT_R)
               pc = pc0 + 3;
               {  if (sp[1].i > sp[0].i) jump(get2(pc0+1)) ; } sp += 2;
               NEXT;

          ACTION(JLEQ_S)
               pc = pc0 + 2;
               {  if (sp[1].i <= sp[0].i) jump(get1(pc0+1)) ; } sp += 2;
               NEXT;

          ACTION(JLEQ_R)
               pc = pc0 + 3;
               {  if (sp[1].i <= sp[0].i) jump(get2(pc0+1)) ; } sp += 2;
               NEXT;

          ACTION(JGEQ_S)
               pc = pc0 + 2;
               {  if (sp[1].i >= sp[0].i) jump(get1(pc0+1)) ; } sp += 2;
               NEXT;

          ACTION(JGEQ_R)
               pc = pc0 + 3;
               {  if (sp[1].i >= sp[0].i) jump(get2(pc0+1)) ; } sp += 2;
               NEXT;

          ACTION(JNEQ_S)
               pc = pc0 + 2;
               {  if (sp[1].i != sp[0].i) jump(get1(pc0+1)) ; } sp += 2;
               NEXT;

          ACTION(JNEQ_R)
               pc = pc0 + 3;
               {  if (sp[1].i != sp[0].i) jump(get2(pc0+1)) ; } sp += 2;
               NEXT;

          ACTION(JLTZ_S)
               pc = pc0 + 2;
               {  if (sp[0].i < 0) jump(get1(pc0+1)) ; } sp += 1;
               NEXT;

          ACTION(JGTZ_S)
               pc = pc0 + 2;
               {  if (sp[0].i > 0) jump(get1(pc0+1)) ; } sp += 1;
               NEXT;

          ACTION(JLEQZ_S)
               pc = pc0 + 2;
               {  if (sp[0].i <= 0) jump(get1(pc0+1)) ; } sp += 1;
               NEXT;

          ACTION(JGEQZ_S)
               pc = pc0 + 2;
               {  if (sp[0].i >= 0) jump(get1(pc0+1)) ; } sp += 1;
               NEXT;

          ACTION(JNEQZ_S)
               pc = pc0 + 2;
               {  if (sp[0].i != 0) jump(get1(pc0+1)) ; } sp += 1;
               NEXT;

          ACTION(JNEQZ_R)
               pc = pc0 + 3;
               {  if (sp[0].i != 0) jump(get2(pc0+1)) ; } sp += 1;
               NEXT;

          ACTION(JEQZ_S)
               pc = pc0 + 2;
               {  if (sp[0].i == 0) jump(get1(pc0+1)) ; } sp += 1;
               NEXT;

          ACTION(JEQZ_R)
               pc = pc0 + 3;
               {  if (sp[0].i == 0) jump(get2(pc0+1)) ; } sp += 1;
               NEXT;

          ACTION(JUMP_S)
               pc = pc0 + 2;
               {  jump(get1(pc0+1)) ; }
               NEXT;

          ACTION(JUMP_R)
               pc = pc0 + 3;
               {  jump(get2(pc0+1)) ; }
               NEXT;

          ACTION(QPLUS)
               pc = pc0 + 1;
               putlong(&sp[2],  getlong(&sp[2]) + getlong(&sp[0]) ); sp += 2;
               NEXT;

          ACTION(QMINUS)
               pc = pc0 + 1;
               putlong(&sp[2],  getlong(&sp[2]) - getlong(&sp[0]) ); sp += 2;
               NEXT;

          ACTION(QTIMES)
               pc = pc0 + 1;
               putlong(&sp[2],  getlong(&sp[2]) * getlong(&sp[0]) ); sp += 2;
               NEXT;

          ACTION(QUMINUS)
               pc = pc0 + 1;
               putlong(&sp[0],  - getlong(&sp[0]) );
               NEXT;

          ACTION(QDIV)
               pc = pc0 + 1;
               {  long_div(sp) ; } sp += 2;
               NEXT;

          ACTION(QMOD)
               pc = pc0 + 1;
               {  long_mod(sp) ; } sp += 2;
               NEXT;

          ACTION(QCMP)
               pc = pc0 + 1;
               sp[3].i =  lcmp(getlong(&sp[2]), getlong(&sp[0])) ; sp += 3;
               NEXT;

          ACTION(JCASE_1)
               pc = pc0 + 2;
               { 
     if ((unsigned) sp[0].i < (unsigned) get1(pc0+1))
          pc0 = pc + 2*sp[0].i, jump(get2(pc0)); else pc += 2*get1(pc0+1);
; } sp += 1;
               NEXT;

          ACTION(JRANGE_S)
               pc = pc0 + 2;
               { 
     if (sp[2].i >= sp[1].i && sp[2].i <= sp[0].i) jump(get1(pc0+1));
; } sp += 3;
               NEXT;

          ACTION(JRANGE_R)
               pc = pc0 + 3;
               { 
     if (sp[2].i >= sp[1].i && sp[2].i <= sp[0].i) jump(get2(pc0+1));
; } sp += 3;
               NEXT;

          ACTION(TESTGEQ_S)
               pc = pc0 + 2;
               { 
     if (sp[1].i >= sp[0].i) jump(get1(pc0+1))
; } sp++;
               NEXT;

          ACTION(TESTGEQ_R)
               pc = pc0 + 3;
               { 
     if (sp[1].i >= sp[0].i) jump(get2(pc0+1))
; } sp++;
               NEXT;

          ACTION(FPLUS)
               pc = pc0 + 1;
               sp[1].f =  sp[1].f + sp[0].f ; sp++;
               NEXT;

          ACTION(FMINUS)
               pc = pc0 + 1;
               sp[1].f =  sp[1].f - sp[0].f ; sp++;
               NEXT;

          ACTION(FTIMES)
               pc = pc0 + 1;
               sp[1].f =  sp[1].f * sp[0].f ; sp++;
               NEXT;

          ACTION(FDIV)
               pc = pc0 + 1;
               sp[1].f =  sp[1].f / sp[0].f ; sp++;
               NEXT;

          ACTION(FUMINUS)
               pc = pc0 + 1;
               sp[0].f =  - sp[0].f ;
               NEXT;

          ACTION(FCMPL)
               pc = pc0 + 1;
               sp[1].i =  fcmpl(sp[1].f, sp[0].f) ; sp++;
               NEXT;

          ACTION(FCMPG)
               pc = pc0 + 1;
               sp[1].i =  fcmpg(sp[1].f, sp[0].f) ; sp++;
               NEXT;

          ACTION(DPLUS)
               pc = pc0 + 1;
               putdbl(&sp[2],  getdbl(&sp[2]) + getdbl(&sp[0]) ); sp += 2;
               NEXT;

          ACTION(DMINUS)
               pc = pc0 + 1;
               putdbl(&sp[2],  getdbl(&sp[2]) - getdbl(&sp[0]) ); sp += 2;
               NEXT;

          ACTION(DTIMES)
               pc = pc0 + 1;
               putdbl(&sp[2],  getdbl(&sp[2]) * getdbl(&sp[0]) ); sp += 2;
               NEXT;

          ACTION(DDIV)
               pc = pc0 + 1;
               putdbl(&sp[2],  getdbl(&sp[2]) / getdbl(&sp[0]) ); sp += 2;
               NEXT;

          ACTION(DUMINUS)
               pc = pc0 + 1;
               putdbl(&sp[0],  - getdbl(&sp[0]) );
               NEXT;

          ACTION(DCMPL)
               pc = pc0 + 1;
               sp[3].i =  fcmpl(getdbl(&sp[2]), getdbl(&sp[0])) ; sp += 3;
               NEXT;

          ACTION(DCMPG)
               pc = pc0 + 1;
               sp[3].i =  fcmpg(getdbl(&sp[2]), getdbl(&sp[0])) ; sp += 3;
               NEXT;

          ACTION(CONVNF)
               pc = pc0 + 1;
               sp[0].f =  flo_conv(sp[0].i) ;
               NEXT;

          ACTION(CONVND)
               pc = pc0 + 1;
               sp--; putdbl(&sp[0],  flo_conv(sp[1].i) );
               NEXT;

          ACTION(CONVFN)
               pc = pc0 + 1;
               sp[0].i =  (int) sp[0].f ;
               NEXT;

          ACTION(CONVDN)
               pc = pc0 + 1;
               sp[1].i =  (int) getdbl(&sp[0]) ; sp++;
               NEXT;

          ACTION(CONVFD)
               pc = pc0 + 1;
               sp--; putdbl(&sp[0],  sp[1].f );
               NEXT;

          ACTION(CONVDF)
               pc = pc0 + 1;
               sp[1].f =  (float) getdbl(&sp[0]) ; sp++;
               NEXT;

          ACTION(CONVNC)
               pc = pc0 + 1;
               sp[0].i =  sp[0].i & 0xff ;
               NEXT;

          ACTION(CONVNS)
               pc = pc0 + 1;
               sp[0].i =  (short) sp[0].i ;
               NEXT;

          ACTION(CONVNQ)
               pc = pc0 + 1;
               sp--; putlong(&sp[0],  sp[1].i );
               NEXT;

          ACTION(CONVQN)
               pc = pc0 + 1;
               sp[1].i =  (int) getlong(&sp[0]) ; sp++;
               NEXT;

          ACTION(CONVQD)
               pc = pc0 + 1;
               putdbl(&sp[0],  flo_convq(getlong(&sp[0])) );
               NEXT;

          ACTION(BOUND_2)
               pc = pc0 + 3;
               {  if ((unsigned) sp[1].i > (unsigned) sp[0].i) error(E_BOUND, get2(pc0+1)) ; } sp++;
               NEXT;

          ACTION(NCHECK_2)
               pc = pc0 + 3;
               {  if (pointer(sp[0]) == NULL) error(E_NULL, get2(pc0+1)) ; }
               NEXT;

          ACTION(GCHECK_2)
               pc = pc0 + 3;
               {  if (valptr(sp[0]) != NULL) error(E_GLOB, get2(pc0+1)) ; } sp += 1;
               NEXT;

          ACTION(ZCHECK_2)
               pc = pc0 + 3;
               {  if (sp[0].i == 0) error(E_DIV, get2(pc0+1)) ; }
               NEXT;

          ACTION(FZCHECK_2)
               pc = pc0 + 3;
               {  if (sp[0].f == 0.0) error(E_FDIV, get2(pc0+1)) ; }
               NEXT;

          ACTION(DZCHECK_2)
               pc = pc0 + 3;
               {  if (get_double(&sp[0]) == 0.0) error(E_FDIV, get2(pc0+1)) ; }
               NEXT;

          ACTION(QZCHECK_2)
               pc = pc0 + 3;
               {  if (get_long(&sp[0]) == 0) error(E_DIV, get2(pc0+1)) ; }
               NEXT;

          ACTION(ERROR_12)
               pc = pc0 + 4;
               {  error(get1(pc0+1), get2(pc0+2)) ; }
               NEXT;

          ACTION(ALIGNC)
               pc = pc0 + 1;
               sp[0].i =  alignx(sp[0].i, 8) ;
               NEXT;

          ACTION(ALIGNS)
               pc = pc0 + 1;
               sp[0].i =  alignx(sp[0].i, 16) ;
               NEXT;

          ACTION(FIXCOPY)
               pc = pc0 + 1;
               { 
    prof_charge(sp[0].i/4);
    memcpy(pointer(sp[2]), pointer(sp[1]), sp[0].i);
; } sp += 3;
               NEXT;

          ACTION(FLEXCOPY)
               pc = pc0 + 1;
               { 
     value *d = (value *) pointer(sp[1]); int size = sp[0].i;           
     int sizew = (size+3)/4; prof_charge(sizew);                        
     sp -= sizew - 2;                                                   
     if ((uchar *) sp < stack + SLIMIT) error(E_STACK, 0);              
     memcpy(sp, pointer(d[0]), size);                                   
     d[0].a = address(sp);
; }
               NEXT;

          ACTION(LINK)
               pc = pc0 + 1;
               {  statlink = valptr(sp[0]) ; } sp += 1;
               NEXT;

          ACTION(SAVELINK)
               pc = pc0 + 1;
               {  bp[SL].a = address(statlink) ; }
               NEXT;

          ACTION(JPROC)
               pc = pc0 + 1;
               { 
     value *p = valptr(sp[0]);
     sp -= HEAD-1; sp[BP].a = address(bp); sp[PC].a = codeaddr(pc);

     if (interpreted(p)) {
          cp = p; pc = codeptr(cp[CP_CODE]);
          goto enter;
     }

#ifdef PROFILE
     /* Calling a native-code routine */
    prof_enter(p, ticks, PROF_PRIM);
    ticks = 0;
#endif
#ifdef OBXDEB
    prim_bp = sp;
#endif
    primcall(p, sp);
#ifdef OBXDEB
    prim_bp = NULL;
#endif
; }
               NEXT;

          ACTION(SLIDE_1)
               pc = pc0 + 2;
               {  slide(get1(pc0+1)) ; }
               NEXT;

          ACTION(SLIDEW_1)
               pc = pc0 + 2;
               {  slide(get1(pc0+1)); sp--; sp[0].i = ob_res.i ; }
               NEXT;

          ACTION(SLIDEF_1)
               pc = pc0 + 2;
               {  slide(get1(pc0+1)); sp--; sp[0].f = ob_res.f ; }
               NEXT;

          ACTION(SLIDED_1)
               pc = pc0 + 2;
               {  slide(get1(pc0+1)); sp -= 2; putdbl(&sp[0], getdbl(&ob_res)) ; }
               NEXT;

          ACTION(SLIDEQ_1)
               pc = pc0 + 2;
               {  slide(get1(pc0+1)); sp -= 2; putlong(&sp[0], getlong(&ob_res)) ; }
               NEXT;

          ACTION(RESULTW)
               pc = pc0 + 1;
               {  ob_res = sp[0] ; } sp += 1;
               NEXT;

          ACTION(RESULTF)
               pc = pc0 + 1;
               {  ob_res.f = sp[0].f ; } sp += 1;
               NEXT;

          ACTION(RESULTQ)
               pc = pc0 + 1;
               {  putlong(&ob_res, getlong(&sp[0])) ; } sp += 2;
               NEXT;

          ACTION(RESULTD)
               pc = pc0 + 1;
               {  putdbl(&ob_res, getdbl(&sp[0])) ; } sp += 2;
               NEXT;

          ACTION(RETURN)
               pc = pc0 + 1;
               { 
     if (bp == base) {
          level--;
#ifdef PROFILE
          prof_exit(NULL, ticks);
#endif
          return;
     }

     sp = bp; pc = codeptr(sp[PC]); bp = valptr(sp[BP]); cp = valptr(bp[CP]);
     do_find_proc;
#ifdef PROFILE
     prof_exit(cp, ticks);
     ticks = 0;
#endif
     cond_break();
; }
               NEXT;

          ACTION(LNUM_2)
               pc = pc0 + 3;
               { 
#ifdef PROFILE
     if (lflag) {
          static module m = NULL; /* Cache most recent module */
          ticks--;
          if (m == NULL || cp < (value *) m->m_addr 
                || cp >= (value *) (m->m_addr + m->m_length)) {
               m = find_module(cp);
         }
          m->m_lcount[get2(pc0+1)-1]++; 
     }
#endif
#ifdef OBXDEB
     if (intflag)
          debug_break(cp, bp, pc0, "interrupt");
     else if (one_shot) 
          debug_break(cp, bp, pc0, "line");
#endif
; }
               NEXT;

          ACTION(BREAK_2)
               pc = pc0 + 3;
               { 
#ifdef OBXDEB
     debug_break(cp, bp, pc0, "break");
#endif
; }
               NEXT;


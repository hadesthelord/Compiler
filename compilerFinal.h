#include<cstdio>
#include<cstdlib>
#include<string>
#include<set>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<vector>
using   namespace   std;

#define nkw 22
#define al 10
#define llng 121
#define kmax 15
#define tmax 100
#define bmax 20
#define amax 30
#define c2max 20
#define cmax 800
#define lmax 7
#define xmax 32767
#define nsy 11
#define tsmax 200
#define synum 49
#define ermax 63
#define lineleng 1000
#define linelimit 1000
#define nmax 32767
#define stacksize 4960
#define smax 600

enum sybol{nul,ident,intsy,realsy,charsy,plusy,minusy,intcon,realcon,charcon,
	timess,divs,eql,neq,lss,leq,gtr,geq,lparent,rparent,lbrack,rbrack,comma,
	semicolon,period,becomes,beginsy,endsy,ifsy,thensy,elsesy,whilesy,
	dosy,forsy,downsy,tosy,writesy,readsy,constsy,
	varsy,procsy,funcsy,oddsy,arraysy,ofsy,notsy,colon,stringsy
};
typedef set<sybol> syset;

enum object{
	constants,
	variable,
	procedur,
	function,
};

enum typs{
	notyp,
	chars,
	ints,
	reals,
	arrays,
	bools
};
typedef set<typs> typset;

struct instruction
{
	int f;
	int x;
	int y;
};

struct tablestruction
{
	char name[al];
	enum object kind;
	enum typs typ;
	enum typs eltp;
	int lev;
	int adr;
	int link;
	int ref;
	bool normal;
};
struct tablestruction tab[tmax];

struct arraytable
{
	enum typs eltyp;
	int elsize,size;
};
struct arraytable atab[amax];

struct blocktable
{
	int last,lastpar,psize,vsize;
};
struct blocktable btab[bmax];

struct conrec
{
	typs tp;
	int i;
	double r;
};
struct item
{
	typs typ;
	int ref;
	enum typs eltp;
};

FILE* fin,*fout,*flist;
char ch;
int i,j;
int inum;
int t;
int a;
int b;
int sx;
int c1;
int c2;
int cc; 
int ll;
int kk;
int cx;
int lc;
bool listswitch;
bool tableswitch;
int errpos;
int sleng;
enum sybol sy;
typedef char alfa[al+1];
alfa id;
double rnum;
char line[llng];
char chr;
struct instruction code[cmax];
char key[nkw][al];
enum sybol ksy[nkw];
enum sybol sps[256];
char mnemonic[29][5];
//char errmsg[62][30];
bool skipflag,iflag,oflag,prtables,stackdump;
typset stantyps;
syset constbegsys,blockbegsys,facbegsys,statbegsys;
char objectcode[5];
char typescode[7];
char stab[smax];
vector<int> errs;
int display[lmax];
double rconst[c2max];
syset kong;


void endskip();
void nextch();
void insybol();
syset add(syset s1,syset s2);
void fatal(int n);
void error(int n);
//void options();
//void switchs(bool b);
void enter2(alfa x0,object x1,typs x2,int x3);
void enterblock();
void enterreal(float x);
void emit(int fcts,int a,int b);
void printtables();
void block(syset fsys,bool isfun,int level);
void skip(syset fsys,int n);
void test(syset s1,syset s2,int n);
void testsemicolon(syset fsys);
void enter1(alfa id,object k,int level);
int loc(alfa id,int level);
void entervariable(int level);
void constant(syset fsys,struct conrec *c,int level);
void parameterlist(syset fsys,int level,int *dx);
void constdec(syset fsys,int level);
void variabledec(syset fsys,int level,int *dx);
void procdeclaration(syset fsys,int level);
void statement(syset fsys,int level);
void expression(syset fsys,struct item *x,int level);
void condition(syset fsys,struct item *x,int level);
void selector(syset fsys,struct item *v,int level,int i);
typs resulttype(typs a,typs b);
void term(syset fsys,struct item *x,int level);
void factor(syset fsys,struct item *x,int level);
void call(syset fsys,int i,int level);
void assignment(syset fsys,int lv,int ad,int i,int level);
void compoundstatement(syset fsys,int level);
void ifstatement(syset fsys,int level);
void whilestatement(syset fsys,int level);
void forstatement(syset fsys,int level);
void standio(syset fsys,int level);
void interpret();
//void dump();
void setup();

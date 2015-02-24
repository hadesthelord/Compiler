#include "compilerFinal.h"

int main()
{
	char fname[200];
	scanf("%s", fname);
	fin=fopen(fname, "r");
	fout=fopen("result.txt","w");
	flist=fopen("list.txt","w");
	setup();
	constbegsys.insert(plusy);
	constbegsys.insert(minusy);
	constbegsys.insert(intsy);
	constbegsys.insert(realsy);
	constbegsys.insert(charsy);
	constbegsys.insert(ident);
	constbegsys.insert(arraysy);
	blockbegsys.insert(constsy);
	blockbegsys.insert(varsy);
	blockbegsys.insert(procsy);
	blockbegsys.insert(funcsy);
	blockbegsys.insert(beginsy);
	facbegsys.insert(intsy);
	facbegsys.insert(realsy);
	facbegsys.insert(charsy);
	facbegsys.insert(ident);
	facbegsys.insert(lparent);
	statbegsys.insert(beginsy);
	statbegsys.insert(ifsy);
	statbegsys.insert(whilesy);
	statbegsys.insert(forsy);
	statbegsys.insert(writesy);
	statbegsys.insert(readsy);
	stantyps.insert(notyp);
	stantyps.insert(ints);
	stantyps.insert(reals);
	stantyps.insert(chars);
	lc=0;
	ll=0;
	cc=0;
	ch=' ';
	errpos=0;
	t=-1;
	a=0;
	b=1;
	sx=0;
	c2=0;
	enter2("",procedur,notyp,0);
	btab[1].last=t;
	btab[1].lastpar=1;
	btab[1].psize=0;
	btab[1].vsize=0;
	display[0]=1;
	iflag=false;
	oflag=false;
	skipflag=false;
//	prtable=false;
	stackdump=false;
	insybol();
	block(add(blockbegsys,statbegsys),false,1);
	if(sy!=period)
	{
		error(1);	//缺少；
	}
	emit(23,0,0);
	if(errs.size()==0)
	{
		printtables();
		interpret();
	}
	else
	{
		printf("compile with error(s)\n");
		fprintf(fout,"compile with error(s)\n");
	}
//	printf("What's wrong with you my dear little DAMNED compiler~\n");
	return 0;
}

void printtables()
{
	int i;
	char mne[31][5];
	strcpy(mne[0],"lda");
	strcpy(mne[1],"lod");
	strcpy(mne[2],"ldi");
	strcpy(mne[3],"dis");
	strcpy(mne[4],"inte");
	strcpy(mne[5],"jmp");
	strcpy(mne[6],"jpc");
	strcpy(mne[7],"opr");
	strcpy(mne[8],"f1u");
	strcpy(mne[9],"f2u");
	strcpy(mne[10],"f1d");
	strcpy(mne[11],"f2d");
	strcpy(mne[12],"mks");
	strcpy(mne[13],"cal");
	strcpy(mne[14],"idx");
	strcpy(mne[15],"ldb");
	strcpy(mne[16],"cpb");
	strcpy(mne[17],"ldc");
	strcpy(mne[18],"ldr");
	strcpy(mne[19],"flt");
	strcpy(mne[20],"red");

	strcpy(mne[21],"wrs");
	strcpy(mne[22],"wrt");
	strcpy(mne[23],"hlt");
	strcpy(mne[24],"exp");
	strcpy(mne[25],"exf");
	strcpy(mne[26],"ldt");
	strcpy(mne[27],"sto");
	strcpy(mne[28],"wrl");
	strcpy(mne[29],"rdl");
	strcpy(tab[0].name,"");
	for(i=0;i<lc;i++)
	{
		fprintf(flist,"%10s,%5d,%5d,%5d\n",mne[code[i].f],code[i].f,code[i].x,code[i].y);
		printf("%10s,%5d,%5d,%5d\n",mne[code[i].f],code[i].f,code[i].x,code[i].y);
	}
	for(i=btab[1].last;i<=t;i++)
	{
		fprintf(flist,"%8s,%4d,%4d,%4d,%4d,%4d,%4d,%4d\n",tab[i].name,tab[i].kind,tab[i].lev,tab[i].normal,tab[i].ref,tab[i].typ,tab[i].adr,tab[i].eltp);
		printf("%8s,%4d,%4d,%4d,%4d,%4d,%4d,%4d\n",tab[i].name,tab[i].kind,tab[i].lev,tab[i].normal,tab[i].ref,tab[i].typ,tab[i].adr,tab[i].eltp);
	}
	for(i=1;i<=b;i++)
	{
		fprintf(flist,"%4d,%4d,%4d,%4d\n",btab[i].last,btab[i].lastpar,btab[i].psize,btab[i].vsize);
		printf("%4d,%4d,%4d,%4d\n",btab[i].last,btab[i].lastpar,btab[i].psize,btab[i].vsize);
	}
}

void setup()
{
	strcpy(key[1],"array");
	strcpy(key[2],"begin");
	strcpy(key[3],"char");
	strcpy(key[4],"const");
	strcpy(key[5],"do");
	strcpy(key[6],"downto");
	strcpy(key[7],"else");
	strcpy(key[8],"end");
	strcpy(key[9],"for");
	strcpy(key[10],"function");
	strcpy(key[11],"if");
	strcpy(key[12],"integer");
	strcpy(key[13],"of");
	strcpy(key[14],"procedure");
	strcpy(key[15],"read");
	strcpy(key[16],"real");
	strcpy(key[17],"then");
	strcpy(key[18],"to");
	strcpy(key[19],"var");
	strcpy(key[20],"while");
	strcpy(key[21],"write");

	ksy[1]=arraysy;
	ksy[2]=beginsy;
	ksy[3]=charcon;
	ksy[4]=constsy;
	ksy[5]=dosy;
	ksy[6]=downsy;
	ksy[7]=elsesy;
	ksy[8]=endsy;
	ksy[9]=forsy;
	ksy[10]=funcsy;
	ksy[11]=ifsy;
	ksy[12]=intcon;
    ksy[13]=ofsy;
	ksy[14]=procsy;
	ksy[15]=readsy;
	ksy[16]=realcon;
	ksy[17]=thensy;
	ksy[18]=tosy;
	ksy[19]=varsy;
	ksy[20]=whilesy;
	ksy[21]=writesy;

	sps['+']=plusy;
	sps['-']=minusy;
	sps['*']=timess;
	sps['/']=divs;
	sps['(']=lparent;
	sps[')']=rparent;
	sps['=']=eql;
	sps[',']=comma;
	sps['[']=lbrack;
	sps[']']=rbrack;
	sps[';']=semicolon;
}

syset add(syset s1,syset s2)
{
	set<sybol>::iterator first=s1.begin(),last=s1.end();
	while(first!=last)
	{
		s2.insert(*first);
		first++;
	}
	return s2;
}

void nextch()
{
	if(cc==ll)
	{
		if(feof(fin))
		{
			printf("\n");
			printf("program imcomplete");
			fprintf(fout,"\n");
			fprintf(fout,"program imcomplete");
			exit(0);
		}
		if(errpos!=0)
		{
			if(skipflag)
			{
				endskip();
			}
			printf("\n");
	     	fprintf(fout,"\n");
			errpos=0;
		}
		printf("%5d",lc);
		fprintf(fout,"%5d",lc);
		ll=0;
		cc=0;
		
		fscanf(fin,"%c",&ch);
		while(ch!='\n' && ch!=EOF)
		{
			ll=ll+1;
			printf("%c",ch);
			fprintf(fout,"%c",ch);
			line[ll]=ch;
			ch=fgetc(fin);
			if(ch=='\n')
				break;
			else if(ch==EOF)
				break;
		}
		ll=ll+1;
		line[ll]='\0';
		printf("\n");
		fprintf(fout,"\n");
	}
	cc=cc+1;
	ch=line[cc];
}

void insybol()
{
	int i,j,k,e;
	char ck;
	while(ch==' '||ch=='\t'||ch=='\n'||ch==0)
	{
		nextch();
	}
	if(('a'<=ch&&ch<='z')||('A'<=ch&&ch<='Z'))
	{
		k=0;
		memset(id,0,al+1);
		do
		{
			if(k<al)
			{
				id[k]=ch;
				k=k+1;
			}
			nextch();
		}while(('a'<=ch&&ch<='z')||('A'<=ch&&ch<='Z')||('0'<=ch&&ch<='9'));
		i=1;
		j=nkw;
		do
		{
			k=(i+j)/2;
			if(strcmp(id,key[k])<=0)
				j=k-1;
			if(strcmp(id,key[k])>=0)
				i=k+1;
		}while(i<=j);
		if(i-1>j)
		{
			sy=ksy[k];
		}
		else
		{
			sy=ident;
		}
	}
	else if('0'<=ch&&ch<='9')
	{
		k=0;
		inum=0;
		sy=intsy;			
		do
		{
			inum=inum*10+(int)(ch-'0');
			k=k+1;
			nextch();
		}while('0'<=ch&&ch<='9');
		if(ch=='.')
		{
			nextch();
			if(ch=='.')
			{
				ch=':';
			}
			else
			{
				sy=realsy;	
				rnum=inum*1.0;
				e=0;
				while('0'<=ch&&ch<='9')
				{
					e=e+1;
					rnum=10.0*rnum+(double)(ch-'0');
					nextch();
				}
				if(e==0)
				{
					error(2);	//实数格式错误
				}
				while(e>0)
				{
					rnum=rnum/10.0;
					e=e-1;
				}
			}
		}
	}
	else if(ch==':')
	{
		nextch();
		if(ch=='=')
		{
			sy=becomes;
			nextch();
		}
		else
		{
			sy=colon;
		}
	}
	else if(ch=='<')
	{
		nextch();
		if(ch=='=')
		{
			sy=leq;
			nextch();
		}
		else if(ch=='>')
		{
			sy=neq;
			nextch();
		}
		else
		{
			sy=lss;
		}
	}
	else if(ch=='>')
	{
		nextch();
		if(ch=='=')
		{
			sy=geq;
			nextch();
		}
		else
		{
			sy=gtr;
		}
	}
	else if(ch=='.')
	{
		nextch();
		if(ch=='.')
		{
			sy=colon;
			nextch();
		}
		else
		{
			sy=period;
		}
	}
	else if(ch=='\'')
	{
		k=0;
		nextch();
	    while((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||ch=='\'')
		{
			if(ch=='\'')
			{
				if(k==1)
				{
					sy=charsy;
					inum=(int)(ck);
				}
				else 
				{
					error(3);	// ''中应为字符常量
				}
				nextch();
				break;
			}
			k=k+1;
			ck=ch;
			nextch();
		}
	}
	else if(ch=='\"')
	{
		k=0;
		nextch();
		while((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9')||ch=='\"'||ch==' '|| ch==':' || ch=='=' )
		{
			if(ch=='\"')
			{
				if(k==0)
				{
					sy=stringsy;
					inum=0;
					sleng=0;
				}
				else
				{
					sy=stringsy;
					inum=sx;
					sleng=k;
					sx=sx+k;
				}
			}
			if(sx+k==smax)
			{
				fatal(7);
			}
			else
			{
				stab[sx+k]=ch;
				k=k+1;
			}
			nextch();
		}
	}
	else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='('||ch==')'||ch=='['||ch==']'||ch==','||ch==';'||ch=='=')
	{
		sy=sps[ch];
		nextch();
	}
}

void endskip()
{
	while(errpos<cc)
	{
		errpos=errpos+1;
	}
	skipflag=false;
}

void error(int n)
{
	errs.push_back(n);
	if(errpos==0)
	{
		printf("****");
		fprintf(fout,"****");
	}
	if(cc>errpos)
	{
		errpos=cc+3;
		printf("%d! ", n);
		fprintf(fout,"%d! ", n);
	}
}

void fatal(int n)
{
	alfa msg[8];
	fprintf(fout,"\n");
	printf("\n");
	strcpy(msg[1],"identifier");
	strcpy(msg[2],"procedures");
	strcpy(msg[3],"reals");
	strcpy(msg[4],"arrays");
	strcpy(msg[5],"levels");
	strcpy(msg[6],"code");
	strcpy(msg[7],"strings");
	printf("compiler table for %s is too small",msg[n]);
	fprintf(fout,"compiler table for %s is too small",msg[n]);
	exit(0);
}

void enter1(alfa id,object k,int level)
{
	int j,l;
	if(t==tmax)
	{
		fatal(1);
	}
	else
	{
		strcpy(tab[0].name,id);
		j=btab[display[level]].last;
		l=j;
		while(strcmp(tab[j].name,id)!=0)
		{
			j=tab[j].link;
		}
		if(j!=0)
		{
			error(6);	// 每个分程序在tab中登陆的第一个标识符的link应为0
		}
		else
		{
			t=t+1;
			strcpy(tab[t].name,id);
			tab[t].link=l;
			tab[t].kind=k;
			tab[t].typ=notyp;
			tab[t].ref=0;
			tab[t].lev=level;
			tab[t].adr=0;
			tab[t].normal=false;
			btab[display[level]].last=t;
		}
	}
}


void enter2(alfa x0,object x1,typs x2,int x3)
{
	t=t+1;
	strcpy(tab[t].name,x0);
	tab[t].link=t-1;
	tab[t].kind=x1;
	tab[t].ref=0;
	tab[t].normal=true;
	tab[t].lev=0;
	tab[t].adr=x3;
	tab[t].typ=x2;
}

void enterarray(typs tp,int l,int h)
{
	if(h>xmax)
	{
		error(4);	//  数组太大
		l=0;
		h=0;
	}
	if(a==amax)
	{
		fatal(4);
	}
	else
	{
		a=a+1;
		atab[a].eltyp=tp;
		atab[a].size=h;
	}
}

void enterblock()
{
	if(b==bmax)
	{
		fatal(2);
	}
	else
	{
		b=b+1;
		btab[b].last=0;
		btab[b].lastpar=0;
	}
}

void enterreal(double x)
{
	if(c2==c2max-1)
	{
		fatal(3);
	}
	else
	{
		rconst[c2+1]=x;
		c1=1;
		while(rconst[c1]!=x)
		{
			c1=c1+1;
		}
		if(c1>c2)
		{
			c2=c1;
		}
	}
}

void entervariable(int level)
{
	if(sy==ident)
	{
		enter1(id,variable,level);
		insybol();
	}
	else
	{
		error(8);	// 不是标识符
	}
}

void emit(int fcts,int a,int b)
{
	if(lc==cmax)
	{
		fatal(6);
	}
	else
	{
		code[lc].f=fcts;
		code[lc].x=a;
		code[lc].y=b;
		lc=lc+1;
	}
}

void skip(syset fsys,int n)
{
	error(n);
	skipflag=true;
	while(!fsys.count(sy))
	{
		insybol();
	}
	if(skipflag)
	{
		endskip();
	}
}

void test(syset s1,syset s2,int n)
{
	if(!s1.count(sy))
	{
		skip(add(s1,s2),n);
	}
}

void testsemicolon(syset fsys)
{
	syset s1;
	s1.insert(ident);
	if(sy==semicolon)
	{
		insybol();
	}
	else
	{
		error(5);	// 缺少；
		if(sy==comma||sy==colon)
		{
			insybol();
		}
	}
	test(add(s1,blockbegsys),fsys,6);
}

int loc(alfa id,int level)
{
	int i,j;
	i=level;
	strcpy(tab[0].name,id);
	do{
		j=btab[display[i]].last;
		while(strcmp(tab[j].name,id)!=0)
			j=tab[j].link;
		i=i-1;
	}while(i>=0&&j==0);
	if(j==0)
	{

		error(7);	// 未声明
	}
	return j;
}

void constant(syset fsys,struct conrec *c,int level)
{
	int x,sign;
	syset s1;
	c->tp=notyp;
	c->i=0;
	test(constbegsys,fsys,50);
	if(constbegsys.count(sy))
	{
		if(sy==charsy)
		{
			c->tp=chars;
			c->i=inum;
			insybol();
		}
		else
		{
			sign=1;
			if(sy==plusy||sy==minusy)
			{
				if(sy==minusy)
				{
					sign=-1;
				}
				insybol();
			}
			if(sy==ident)
			{
				x=loc(id,level);
				if(x!=0)
				{
					if(tab[x].kind!=constants)
					{
						error(9);	// 不是常量
					}
					else
					{
						c->tp=tab[x].typ;
						if(c->tp==realsy)
						{
							c->r=sign*rconst[tab[x].adr];
						}
						else
						{
							c->i=sign*tab[x].adr;
						}
					}
					insybol();
				}
			}
			if(sy==intsy)
			{
				c->tp=ints;
				c->i=sign*inum;
				insybol();
			}
			else if(sy==realsy)
			{
				c->tp=reals;
				c->r=sign*rnum;
				insybol();
			}
			else
				skip(fsys,50);
		}
		test(fsys,s1,6);
	}
}

void parameterlist(syset fsys,int level,int *dx)
{
	typs tp;
	bool valpar;
	int t0;
	syset s1,s2,s3,s4,s5;
	s1.insert(ident);
	s1.insert(varsy);
	s2.insert(rparent);
	insybol();
	if(sy==rparent)
		error(62);	// 的参数表不能为空
	tp=notyp;
	while(sy==ident||sy==varsy)
	{
		if(sy!=varsy)
			valpar=true;
		else
		{
			insybol();
			valpar=false;
		}
		t0=t;
		entervariable(level);
		while(sy==comma)
		{
			insybol();
			entervariable(level);
		}
		if(sy==colon)
		{
			insybol();
			if(sy==intcon)
			{
				tp=ints;
				insybol();
			}
			else if(sy==charcon)
			{
				tp=chars;
				insybol();
			}
			else if(sy==realcon)
			{
				tp=reals;
				insybol();
			}
			else
			{
				error(10);	// 不存在此类型
				tp=notyp;
			}
			s3.insert(semicolon);
			s3.insert(rparent);
			s4.insert(comma);
			s4.insert(ident);
			test(s3,add(s4,fsys),14);//应是分号
		}
		else
		{
			error(11);	// 类型声明错误，缺少：
		}
		while(t0<t)
		{
			t0=t0+1;
			tab[t0].typ=tp;
			tab[t0].ref=0;
			tab[t0].adr=*dx;
			tab[t0].lev=level;
			tab[t0].normal=valpar;
			*dx=*dx+1;
		}
		if(sy!=rparent)
		{
			if(sy==semicolon)
			{
				insybol();
			}
			else
			{
				error(12);	// 句尾应有；
				if(sy==comma)
					insybol();
			}
			test(s1,add(s2,fsys),6);
		}
	}
	if(sy==rparent)
	{
		insybol();
		s5.insert(semicolon);
		s5.insert(colon);
		test(s5,fsys,6);
	}
	else
	{
		error(13);	// 缺少）
	}
}

void constdec(syset fsys,int level)
{
	syset s1;
	syset s2;
	struct conrec *c;
	c=(struct conrec*)malloc(sizeof(struct conrec));
	insybol();
	s1.insert(ident);
	test(s1,blockbegsys,2);//应是标识符
	while(sy==ident)
	{
		enter1(id,constants,level);
		insybol();
		if(sy==eql)
			insybol();
		else
		{
			error(14);	// 赋值应用=
			if(sy==becomes)
				insybol();
		}
		s2.insert(semicolon);
		s2.insert(comma);
		s2.insert(ident);
		constant(add(s2,fsys),c,level);
		tab[t].typ=c->tp;
		tab[t].ref=0;
		if(c->tp==reals)
		{
			enterreal(c->r);
			tab[t].adr=c1;
		}
		else
		{
			tab[t].adr=c->i;
		}
		if(sy==comma||sy==semicolon)
		{
			if(sy==semicolon)
			{
				insybol();
				break;
			}
			insybol();
		}
	}
}

void variabledec(syset fsys,int level,int *dx)
{
	syset s1;
	typs tp,etp;
	int t0,t1,sz,i;
	insybol();
	while(sy==ident)
	{
		t0=t;
		entervariable(level);
		while(sy==comma)
		{
			insybol();
			entervariable(level);
		}
		if(sy==colon)
			insybol();
		else
		{
			error(15);	// 类型声明缺少：
		}
		t1=t;
		if(sy==intcon)
		{
			tp=ints;
			insybol();
			for(i=t0+1;i<=t1;i++)
			{
				tab[i].typ=tp;
				tab[i].ref=0;
				tab[i].lev=level;
				tab[i].adr=*dx;
				tab[i].normal=true;
				*dx=*dx+1;
			}
		}
		else if(sy==charcon)
		{
			tp=chars;
			insybol();
			for(i=t0+1;i<=t1;i++)
			{
				tab[i].typ=tp;
				tab[i].ref=0;
				tab[i].lev=level;
				tab[i].adr=*dx;
				tab[i].normal=true;
				*dx=*dx+1;
			}
		}
		else if(sy==realcon)
		{
			tp=reals;
			insybol();
			for(i=t0+1;i<=t1;i++)
			{
				tab[i].typ=tp;
				tab[i].ref=0;
				tab[i].lev=level;
				tab[i].adr=*dx;
				tab[i].normal=true;
				*dx=*dx+1;
			}
		}
		else if(sy==arraysy)
		{
			tp=arrays;
			insybol();
			if(sy!=lbrack)
			{
				error(16);	// 数组缺[
				if(sy==lparent)
					insybol();
			}
			else
				insybol();
			if(sy!=intsy)
			{
				error(17);	// 数组大小只能是无符号整形
				inum=0;
			}
			sz=inum;
			for(i=t0+1;i<=t1;i++)
			{
				tab[i].typ=tp;
				tab[i].ref=sz;
				tab[i].lev=level;
				tab[i].adr=*dx;
				tab[i].normal=true;
				*dx=*dx+sz;
			}
			insybol();
			if(sy==rbrack)
			{
				insybol();
				if(sy!=ofsy)
				{
					error(18);	// 数组声明缺of 
				}
				else
					insybol();
				if(sy==intcon)
				{
					etp=ints;
					insybol();
				}
				else if(sy==charcon)
				{
					etp=chars;
					insybol();
				}
				else if(sy==realcon)
				{
					etp=reals;
					insybol();
				}
				else
				{
					etp=notyp;
					error(19);	// 数组元素只能是整型、实型、字符型
				}
				for(i=t0+1;i<=t1;i++)
					tab[i].eltp=etp;
			}
			else
			{
				error(20);	// 数组缺]
				if(sy==rparent)
				{
					insybol();
					if(sy!=ofsy)
					{
						error(21);	// 数组声明缺of
					}
					else
						insybol();
					if(sy==intcon)
						etp=ints;
					else if(sy==charcon)
						etp=chars;
					else if(sy==realcon)
						etp=reals;
					else
					{
						etp=notyp;
						error(19);	// 数组元素只能是整型、实型、字符型
					}
					for(i=t0+1;i<=t1;i++)
						tab[i].eltp=etp;
				}
			}
			//test(blockbegsys,fsys,6);
		}
		testsemicolon(fsys);
	}
}


///////////////////
///////////////////
///////////////////
void procdeclaration(syset fsys,int level)
{
	syset s1;
	bool isfun;
	s1.insert(semicolon);
	isfun=(sy==funcsy);
	insybol();
	if(sy!=ident)
	{
		error(23);	// 过程名应为标示符
		strcpy(id,"");
	}
	if(isfun)
	{
		enter1(id,function,level);
	}
	else
	{
		enter1(id,procedur,level);
	}
	tab[t].normal=true;
	insybol();
	block(add(s1,fsys),isfun,level+1);
	if(sy==semicolon)
		insybol();
	else
	{
		error(24);	// 函数和过程声明句尾应有；
	}
	if(isfun)
		emit(25,0,0);
	else
		emit(24,0,0);
}

void selector(syset fsys,struct item *v,int level,int i)
{
	struct item *x;
	x=(struct item*)malloc(sizeof(struct item));
	syset s1;
	syset s2;
	s1.insert(comma);
	s1.insert(rbrack);
	//s1.insert(thensy);
	if(v->typ==arrays)
	{
		if(sy!=lbrack)
		{
			error(25);	// 数组引用缺[
		}
		insybol();
		expression(add(fsys,s1),x,level);
		if(x->typ!=ints)
		{
			error(26);	// 数组元素只能是整型
		}
		else
		{
			//emit(14, 0, v->ref);
			emit(14,0,i);
		}
		v->typ=tab[i].eltp;
		v->ref=tab[i].ref;
		if(sy==rbrack)
		{
			insybol();
		}
		else
		{
			error(27);	// 数组引用缺]
			if(sy==rparent)
				insybol();
		}
	}
		//test(fsys,s2,6);
}

void call(syset fsys,int i,int level)
{
	struct item *x;
	syset s1,s2;
	int lastp,cp,k;
	x=(struct item*)malloc(sizeof(struct item));
	emit(12,0,i);
	s1.insert(comma);
	s1.insert(colon);
	s1.insert(rparent);
	s2.insert(comma);
	s2.insert(rparent);
	lastp=btab[tab[i].ref].lastpar;
	cp=i;
	if(sy==lparent)
	{
		do
		{
			if(cp==lastp)
			{
				insybol();
				break;
			}
			insybol();
			if(cp>lastp)
			{
				error(28);	// 无法从此位置调用函数或过程
			}
			else
			{
				cp=cp+1;
				if(tab[cp].normal)
				{
					expression(add(fsys,s1),x,level);
					if(x->typ==tab[cp].typ)
					{
						if(x->ref!=tab[cp].ref)
						{
							error(29);	// 类型不匹配
						}
						else if(x->typ==arrays)//what
						{
							emit(15,0,atab[x->ref].size);
						}
					}
					else if(x->typ==ints&&tab[cp].typ==reals)
					{
						emit(19,0,0);
					}
					else
					{
						if(x->typ!=notyp)
						{
							error(30);	// 参数不能为此类型
						}
					}
				}
				else	//传地址
				{
					if(sy!=ident)
					{
						error(31);	// 参数必须为标识符
					}
					else
					{
						k=loc(id,level);
						insybol();
						if(k!=0)
						{
							if(tab[k].kind==variable)
							{
								x->typ=tab[k].typ;
								x->ref=tab[k].ref;
								x->eltp=tab[k].eltp;
								if(tab[k].typ!=arrays)
								{
									if(tab[k].normal)
									{
										emit(0,tab[k].lev,tab[k].adr);
									}
									else
									{
										emit(1,tab[k].lev,tab[k].adr);
									}
								}
								else
								{
									if(sy==lbrack)
									{
										emit(0, 1, tab[k].adr);
										selector(add(fsys, s1), x, level, k);
									}
									x->typ=tab[k].typ;
									x->ref=tab[k].ref;
									x->eltp=tab[k].eltp;
								}
							}
							else if(tab[k].kind==function)
							{
								x->typ=tab[k].typ;
								x->ref=tab[cp].ref;
								x->eltp=tab[k].eltp;
								if(tab[i].lev!=0)
									call(fsys,k,level);
							}
							else
							{
								error(31);	// 参数必须为标识符
							}

							
							if(x->typ==arrays)
							{
								if(x->eltp!=tab[cp].typ)
									error(32);	// 形、实参类型不匹配
							}
							else if(x->typ!=tab[cp].typ||x->ref!=tab[cp].ref)
							{
								error(32);	// 形、实参类型不匹配
							}
						}
					}
				}
				//test(s2,fsys,6);
			}
		}while(sy==comma);
		if(sy==rparent)
			insybol();
		else
		{
			error(33);	// 参数表缺）
		}
	}
	if(cp<lastp)
	{
		error(34);	// 调用错误
	}
	emit(13,0,btab[tab[i].ref].psize-1);
	if(tab[i].lev<level)
	{
		emit(3,tab[i].lev,level);
	}
}

typs resulttype(typs a,typs b)
{
	if(a==notyp||b==notyp)
	{
		return(notyp);
	}
	else if(a==arrays||b==arrays)
	{
		error(35);	// 参与运算的元素类型不对
		return(notyp);
	}
	else if(a==chars&&b==chars)
	{
		return(ints);
	}
	else if(a==chars&&b==ints)
	{
		return(ints);
	}
	else if(a==ints&&b==chars)
	{
		return(ints);
	}
	else if(a==chars&&b==reals)
	{
		emit(19,0,1);
		return(reals);
	}
	else if(a==reals&&b==chars)
	{
		emit(19,0,0);
		return(reals);
	}
	else if(a==ints&&b==ints)
	{
		return(ints);
	}
	else if(a==ints&&b==reals)
	{
		emit(19,0,1);
		return(reals);
	}
	else if(a==reals&&b==ints)
	{
		emit(19,0,0);
		return(reals);
	}
	else if(a==reals&&b==reals)
	{
		return(reals);
	}
}


void block(syset fsys,bool isfun,int level)
{
	struct conrec *c;
	int prt,prb,d=5;
	int *dx;
	syset s1,s2,s3,s4,s5;
	c=(struct conrec*)malloc(sizeof(struct conrec));;
	s2.insert(semicolon);
	s1.insert(lparent);
	s1.insert(colon);
	s1.insert(semicolon);
	s3.insert(semicolon);
	s3.insert(endsy);
	s4.insert(period);
	s5.insert(beginsy);
	dx=&d;
	prt=t;
	if(level>lmax)
	{
		fatal(5);
	}
	enterblock();
	prb=b;
	display[level]=b;
	tab[prt].typ=notyp;
	tab[prt].ref=prb;
	if(sy==lparent&&level>1)
	{
		parameterlist(fsys,level,dx);
	}
	btab[prb].lastpar=t;
	btab[prb].psize=*dx;
	if(isfun)
	{
		if(sy==colon)
		{
			insybol();
			if(sy==intcon)
			{
				insybol();
				tab[prt].typ=ints;
			}
			else if(sy==charcon)
			{
				insybol();
				tab[prt].typ=chars;
			}
			else if(sy==realcon)
			{
				insybol();
				tab[prt].typ=reals;
			}
			else
			{
				skip(add(s2,fsys),2);
			}
		}
		else
		{
			error(59);	// 函数必须有返回值
		}
	}
	if(sy==semicolon)
	{
		insybol();
	}
	do{
		if(sy==constsy)
		{
			constdec(fsys,level);
		}
		if(sy==varsy)
		{
			variabledec(fsys,level,dx);
		}
		btab[prb].vsize=*dx;
		while(sy==procsy||sy==funcsy)
		{
			procdeclaration(fsys,level);
		}
		test(s5,add(blockbegsys,statbegsys),56);
	}while(!statbegsys.count(sy));
	tab[prt].adr=lc;
	if(sy==beginsy)
	{
		insybol();
	}
	else 
	{
		error(61);	// 语句缺begin
	}
	compoundstatement(add(fsys,s3),level);
	if(sy==endsy)
	{
		insybol();
	}
//	test(add(fsys,s4),s4,6);
}

void statement(syset fsys,int level)
{
	int i;
	struct item *x;
	syset s1;
	x=(struct item*)malloc(sizeof(struct item));
	s1.insert(ident);
	s1=add(statbegsys,s1);
	if(s1.count(sy))
	{
		if(sy==ident)
		{
			i=loc(id,level);
			insybol();
			if(i!=0)
			{
				if(tab[i].kind==constants)
				{
					error(57);	// 常量不能被赋值
				}
				else if(tab[i].kind==variable)
				{
					assignment(fsys,tab[i].lev,tab[i].adr,i,level);
				}
				else if(tab[i].kind==procedur)
				{
					call(fsys,i,level);
				}
				else 
				{
					if(tab[i].ref==display[level])
					{
						assignment(fsys,tab[i].lev+1,0,i,level);
					}
					else
					{
						error(58);	// 不能引用该层变量
					}
				}
			}
		}
		else if(sy==beginsy)
		{
			insybol();
			compoundstatement(fsys,level);
		}
		else if(sy==ifsy)
		{
			ifstatement(fsys,level);
		}
		else if(sy==whilesy)
		{
			whilestatement(fsys,level);
		}
		else if(sy==forsy)
		{
			forstatement(fsys,level);
		}
		else if(sy==readsy||sy==writesy)
		{
			standio(fsys,level);
			//readstatement(fsys,level);
			//writestatement(fsys,level);
		}
	}
	//test(fsys,kong,14);
}

void expression(syset fsys,struct item *x,int level)
{
	struct item *y;
	y=(struct item*)malloc(sizeof(struct item));
	sybol op;
	syset s1;
	s1.insert(plusy);
	s1.insert(minusy);
	if(sy==plusy||sy==minusy)
	{
		op=sy;
		insybol();
		term(add(fsys,s1),x,level);
		if(x->typ==arrays)
		{
			error(37);	// 参与运算的类型错误
		}
		else
		{
			if(op==minusy)
				emit(7,0,20);
		}
	}
	else 
	{
		term(add(fsys,s1),x,level);
	}
	while(s1.count(sy))
	{
		op=sy;
		insybol();
		term(add(fsys,s1),y,level);
		x->typ=resulttype(x->typ,y->typ);
		if(x->typ==ints)
		{
			if(op==plusy)
				emit(7,0,12);
			else 
				emit(7,0,13);
		}
		else if(x->typ==reals)
		{
			if(op==plusy)
				emit(7,0,14);
			else 
				emit(7,0,15);
		}
	}
}


void term(syset fsys,struct item *x,int level)
{
	struct item *y;
	y=(struct item*)malloc(sizeof(struct item));
	sybol op;
	typset ts;
	syset s1;
	s1.insert(timess);
	s1.insert(divs);
	factor(add(fsys,s1),x,level);
	while(s1.count(sy))
	{
		op=sy;
		insybol();
		factor(add(fsys,s1),y,level);
		if(op==timess)
		{
			x->typ=resulttype(x->typ,y->typ);
			if(x->typ==ints)
			{
				emit(7,0,16);
			}
			else if(x->typ==reals)
			{
				emit(7,0,18);
			}
		}
		else if(op==divs)
		{
			x->typ=resulttype(x->typ,y->typ);
			if(x->typ==ints)
			{
				emit(7,0,17);
			}
			else if(x->typ==reals)
			{
				emit(7,0,19);
			}
		}
	}
}

void factor(syset fsys,struct item *x,int level)
{
	syset s1,s2;
	s1.insert(lbrack);
	s1.insert(lparent);
	s2.insert(rbrack);
	x->typ=notyp;
	x->ref=0;
//	test(facbegsys,fsys,58);
	while(facbegsys.count(sy))
	{
		if(sy==ident)
		{
			i=loc(id,level);
			insybol();
			if(tab[i].kind==constants)
			{
				x->typ=tab[i].typ;
				x->ref=0;
				if(x->typ==reals)
				{
					emit(18,0,tab[i].adr);
					//emit(18, 0, rconst[tab[i].adr]);
				}
				else
				{
					/////
					emit(17, 0, tab[i].adr);
				}
			}
			else if(tab[i].kind==variable)
			{
				x->typ=tab[i].typ;
				x->ref=tab[i].ref;
				if(x->typ==ints||x->typ==chars||x->typ==reals)//question
				{
					if(tab[i].normal)
					{
						emit(1,tab[i].lev,tab[i].adr);
					}
					else
					{
						emit(2,tab[i].lev,tab[i].adr);
					}
				}
				else if(x->typ==arrays)
				{
					if(sy==lbrack)
					{
						if(tab[i].normal)
						{
							emit(0,tab[i].lev,tab[i].adr);
						}
						else
						{
							emit(1,tab[i].lev,tab[i].adr);
						}
						selector(fsys,x,level,i);
						if(stantyps.count(x->typ))
							emit(26,0,0);
					}
				}
			}
			else if(tab[i].kind==function)
			{
				x->typ=tab[i].typ;
				if(tab[i].lev!=0)
				{
					call(fsys,i,level);
				}
			}
		}
		else if(sy==intsy||sy==realsy||sy==charsy)
		{
			if(sy==realsy)
			{
				x->typ=reals;
				enterreal(rnum);
				emit(18,0,c1);
			}
			else if(sy==intsy)
			{
				x->typ=ints;
				emit(17,0,inum);
			}
			//else if(sy==charsy)
			//{
			//	x->typ=chars;
			//	emit(17,0,inum);
			//}
			else
				error(22);	// 字符不能直接参与运算
			x->ref=0;
			insybol();
		}
		else if(sy==lparent)
		{
			insybol();
			expression(add(fsys,s2),x,level);
			if(sy==rparent)
			{
				insybol();
			}
			else
			{
				error(36);	// 缺少）
			}
		}
		//test(fsys,facbegsys,6);
	}
}

void assignment(syset fsys,int lv,int ad,int i,int level)
{
	struct item *x,*y;
	syset s1;
	x=(struct item*)malloc(sizeof(struct item));
	y=(struct item*)malloc(sizeof(struct item));
	s1.insert(becomes);
	s1.insert(eql);
	x->typ=tab[i].typ;
	x->ref=tab[i].ref;
	if(tab[i].normal)
	{
		emit(0,lv,ad);
	}
	else
	{
		emit(1,lv,ad);
	}
	if(sy==lbrack)
	{
		selector(add(fsys,s1),x,level,i);
	}
	if(sy==becomes)
	{
		insybol();
	}
	else
	{
		error(38);	// 赋值符号应为：=
		if(sy==eql)
			insybol();
	}
	expression(fsys,y,level);
	if(x->typ==y->typ)
	{
		if(stantyps.count(y->typ))
		{
			emit(27,0,0);
		}
		else
		{
			error(39);	// 赋值号两边元素类型不匹配
		}
	}
	else if(x->typ==reals&&y->typ==ints)
	{
		emit(19,0,0);
		emit(27,0,0);
	}
	else
	{
		if(x->typ==chars&&y->typ==ints)
		{
			emit(27,0,0);
		}
		else if(x->typ==ints&&y->typ==chars)
		{
			emit(27,0,0);
		}
		else if(x->typ==reals&&y->typ==chars)
		{
			emit(19,0,0);
			emit(27,0,0);
		}
		else
		{
			if(x->typ!=notyp&&y->typ!=notyp)
			{
					error(40);	// 不允许这两种类型之间赋值
			}
		}
	}
}

void compoundstatement(syset fsys,int level)
{
	syset s1,s2;
	s1.insert(semicolon);
	s1.insert(endsy);
	s2.insert(semicolon);
	statement(add(s1,fsys),level);
	s2=add(s2,statbegsys);
	while(s2.count(sy))
	{
		if(sy==semicolon)
		{
			insybol();
		}
		else
		{
			error(41);	// 缺少；
		}
		statement(add(s1,fsys),level);
	}
	if(sy==endsy)
	{
		insybol();
	}
	else
	{
		error(42);	// 缺少end 
	}
}

void condition(syset fsys,struct item *x,int level)
{
	struct item *y;
	sybol op;
	typset s2;
	syset s1;
	y=(struct item*)malloc(sizeof(struct item));
	s1.insert(eql);
	s1.insert(neq);
	s1.insert(lss);
	s1.insert(leq);
	s1.insert(gtr);
	s1.insert(geq);
	s2.insert(notyp);
	s2.insert(ints);
	s2.insert(bools);
	s2.insert(chars);
	expression(add(fsys,s1),x,level);
	if(s1.count(sy))
	{
		op=sy;
		insybol();
		expression(fsys,y,level);
		if(s2.count(x->typ)&&x->typ==y->typ)
		{
			if(op==eql)
				emit(7,0,6);
			else if(op==neq)
				emit(7,0,7);
			else if(op==lss)
				emit(7,0,8);
			else if(op==leq)
				emit(7,0,9);
			else if(op==gtr)
				emit(7,0,10);
			else if(op==geq)
				emit(7,0,11);
		}
		else 
		{
			if(x->typ==ints)
			{
				x->typ=reals;
				emit(19,0,1);
			}
			else 
			{
				if(y->typ==ints)
				{
					y->typ=reals;
					emit(19,0,0);
				}
			}
			if(x->typ==reals&&y->typ==reals)
			{
				if(op==eql)
					emit(7,0,0);
				else if(op==neq)
					emit(7,0,1);
				else if(op==lss)
					emit(7,0,2);
				else if(op==leq)
					emit(7,0,3);
				else if(op==gtr)
					emit(7,0,4);
				else if(op==geq)
					emit(7,0,5);
			}
			else
			{
				error(60);	// 此两种数据类型不能比较
			}
		}
		x->typ=bools;
	}
}

void ifstatement(syset fsys,int level)
{
	int lc1,lc2;
	struct item *x;
	syset s1;
	x=(struct item*)malloc(sizeof(struct item));
	s1.insert(elsesy);
	insybol();
	condition(fsys,x,level);
	if(x->typ!=bools&&x->typ!=notyp)
	{
		error(43);	// 条件语句中的标识符类型有错误
	}	
	lc1=lc;
	emit(6,0,0);
	if(sy==thensy)
		insybol();
	else
	{
		error(44);	// 缺少then 
		if(sy==dosy)
			insybol();
	}
	statement(add(fsys,s1),level);
	if(sy==elsesy)
	{
		insybol();
		lc2=lc;
		emit(5,0,0);
		code[lc1].y=lc;
		statement(fsys,level);
		code[lc2].y=lc;
	}
	else
		code[lc1].y=lc;
}

void whilestatement(syset fsys,int level)
{
	struct item *x;
	int lc1,lc2;
	syset s1;
	x=(struct item*)malloc(sizeof(struct item));
	s1.insert(dosy);
	insybol();
	lc1=lc;
	condition(add(fsys,s1),x,level);
	if(x->typ!=bools&&x->typ!=notyp)
	{
		error(45);	// 当语句中的标识符类型有错误
	}
	lc2=lc;
	emit(6,0,0);
	if(sy==dosy)
		insybol();
	else 
	{
		error(46);	//  当语句缺少do 
	}
	statement(fsys,level);
	emit(5,0,lc1);
	code[lc2].y=lc;
}

void forstatement(syset fsys,int level)
{
	typs cvt;
	syset s1,s2;
	struct item *x;
	int i,lc1,lc2;
	int f;
	x=(struct item*)malloc(sizeof(struct item));
	s1.insert(tosy);
	s1.insert(downsy);
	s1.insert(dosy);
	s2.insert(dosy);
	insybol();
	if(sy==ident)
	{
		i=loc(id,level);
		insybol();
		if(i==0)
		{
			cvt=ints;
			error(47);	// 应先声明再引用
		}
		else 
		{
			if(tab[i].kind==variable)
			{
				cvt=tab[i].typ;
				if(!tab[i].normal)
				{
					error(48);	// 不能使用变量形参
				}
				else
					emit(0,tab[i].lev,tab[i].adr);
			}
		}
	}
	else
	{
	//	skip();
	}
	if(sy==becomes)
	{
		insybol();
		expression(add(fsys,s1),x,level);
		if(x->typ!=cvt)
		{
			if(cvt==reals&&x->typ==ints)
				emit(19,0,0);
			else
			{
				error(49);	// 只能是整型或实型
			}
		}
	}
	else
	{
		//skip();
	}
	f=8;
	if(sy==tosy||sy==downsy)
	{
		if(sy==downsy)
			f=10;
		insybol();
		expression(add(fsys,s2),x,level);
		if(x->typ!=cvt)
		{
			if(cvt==reals&&x->typ==ints)
				emit(19,0,0);
			else
			{
				error(49);	// 只能是整型或实型
			}
		}
	}
	else
	{
		//skip();
		error(50);	// 应为to或downto
	}
	lc1=lc;
	if(cvt==reals)
	{
		emit(f,1,0);
	}
	else
	{
		emit(f,0,0);
	}
	if(sy==dosy)
		insybol();
	else
	{
		error(51);	// for语句缺少do
	}	
	lc2=lc;
	statement(fsys,level);
	if(cvt==reals)
	{
		if(f==8)
			emit(9,1,lc2);
		else if(f==10)
			emit(11,1,lc2);
	}
	else
	{
		if(f==8)
			emit(9,0,lc2);
		else if(f==10)
			emit(11,0,lc2);
	}
	code[lc1].y=lc;
}

void standio(syset fsys,int level)
{
	if(sy==readsy)
	{
		int i;
		struct item *x;
		struct item *y;
		x=(struct item*)malloc(sizeof(struct item));
		y=(struct item*)malloc(sizeof(struct item));
		insybol();
		if(sy==lparent)
		{
			do{
				insybol();
				if(sy!=ident)
				{
					error(52);	//	应为标识符
				}
				else
				{
					i=loc(id,level);
					insybol();
					if(i!=0)
					{
						if(tab[i].kind!=variable)
						{
							error(53);	// 只能读入变量
						}
						else
						{
							x->typ=tab[i].typ;
							x->ref=tab[i].ref;
							if(tab[i].normal)
							{
								emit(0,tab[i].lev,tab[i].adr);
							}
							else
							{
								emit(1,tab[i].lev,tab[i].adr);
							}
							if(x->typ==ints)
							{
								emit(20,0,1);
							}
							else if(x->typ==reals)
							{
								emit(20,0,2);
							}
							else if(x->typ==chars)
							{
								emit(20,0,3);
							}
							else
							{
								error(54);	// 只能读入整型、实型、字符型
							}
						}
					}
				}
			}while(sy==comma);
			if(sy==rparent)
			{
				insybol();
			}
			else
			{
				error(55);	// 读语句缺少）
			}
		}
	}
	else	//write
	{
		struct item *x;
		struct item *y;
		syset s1;
		x=(struct item*)malloc(sizeof(struct item));
		y=(struct item*)malloc(sizeof(struct item));
		s1.insert(rparent);
		insybol();
		if(sy==lparent)
		{
			do{
				insybol();
				if(sy==stringsy)
				{
					emit(17,0,sleng);
					emit(21,0,inum);
					insybol();
					if(sy==comma)
					{
						insybol();
						expression(add(fsys,s1),x,level);
						if(x->typ==ints)
						{
							emit(22,0,1);
						}
						else if(x->typ==reals)
						{
							emit(22,0,2);
						}
						else if(x->typ==chars)
						{
							emit(22,0,3);
						}
					}
				}
				else
				{
					expression(add(fsys,s1),x,level);
					if(x->typ==ints)
					{
						emit(22,0,1);
					}
					else if(x->typ==reals)
					{
						emit(22,0,2);
					}
					else if(x->typ==chars)
					{
						emit(22,0,3);
					}
				}
			}while(sy==comma);
			//if(sy==rparent)
			//{
			//	insybol();
			//}
			//else
			//{
			//	error(56);
			//}
			if(sy!=rparent)
			{
				error(56);	// 写语句缺少）
				insybol();
			}
			else
				insybol();
		}
	}
}	

void interpret()
{
	char ch;
	int pc,t,b,h1,h2,h3,h4,mc;
	float r1;
	int lncnt,ocnt,chrcnt;
	int fld[5];
	enum ps0{run,fine,caschk,divchk,inxchk,stkchk,linchk,lngchk,redchk
	};
	ps0 ps;
	struct blockmark
	{
		int i;
		float r;
		bool b;
		char c;
	}s[stacksize];
	int display[lmax];
	s[1].i=0;
	s[2].i=0;
	s[3].i=-1;
	s[4].i=btab[1].last;
	display[1]=0;
	t=btab[2].vsize-1;
	b=0;
	pc=tab[s[4].i].adr;
	lncnt=0;
	ocnt=0;
	chrcnt=0;
	fld[1]=10;
	fld[2]=22;
	fld[3]=10;
	fld[4]=1;
	ps=run;
	do{
		mc=pc;
		pc=pc+1;
		ocnt=ocnt+1;
		switch(code[mc].f)
		{
		case 0:		// load address
			t=t+1;
			if(t>stacksize)
				ps=stkchk;
			else
				s[t].i=display[code[mc].x]+code[mc].y;
			break;
		case 1:		// load value
			t=t+1;
			if(t>stacksize)
				ps=stkchk;
			else
				s[t]=s[display[code[mc].x]+code[mc].y];
			break;
		case 2:		// load indirect
			t=t+1;
			if(t>stacksize)
				ps=stkchk;
			else
				s[t]=s[s[display[code[mc].x]+code[mc].y].i];
			break;
		case 3:		// update display
			h1=code[mc].y;
			h2=code[mc].x;
			h3=b;
			do{
				display[h1]=h3;
				h1=h1-1;
				h3=s[h3+2].i;
			}while(h1!=h2);
			break;
		case 4:		// offset
			s[t].i=s[t].i+code[mc].y;
			break;
		case 5:		// jump
			pc=code[mc].y;
			break;
		case 6:		// conditional jump
			if(!s[t].b)
			{
				pc=code[mc].y;
			}
			t=t-1;
			break;
		case 8:		// 
			if(code[mc].x==0)
			{
				h1=s[t-1].i;
				if(h1<=s[t].i)
					s[s[t-2].i].i=h1;
				else
				{
					t=t-3;
					pc=code[mc].y;
				}
			}
			else
			{
				r1=s[t-1].r;
				if(r1<=s[t].r)
					s[s[t-2].i].r=r1;
				else
				{
					t=t-3;
					pc=code[mc].y;
				}
			}
			break;
		case 9:
			if(code[mc].x==0)
			{
				h2=s[t-2].i;
				h1=s[h2].i+1;
				if(h1<=s[t].i)
				{
					s[h2].i=h1;
					pc=code[mc].y;
				}
				else
					t=t-3;
			}
			else
			{
				h2=s[t-2].i;
				r1=s[h2].r+1.0;
				if(r1<=s[t].r)
				{
					s[h2].r=r1;
					pc=code[mc].y;
				}
				else
					t=t-3;
			}
			break;
		case 10:
			if(code[mc].x==0)
			{
				h1=s[t-1].i;
				if(h1>=s[t].i)
					s[s[t-2].i].i=h1;
				else
				{
					t=t-3;
					pc=code[mc].y;
				}
			}
			else
			{
				r1=s[t-1].r;
				if(r1>=s[t].r)
					s[s[t-2].i].r=r1;
				else
				{
					t=t-3;
					pc=code[mc].y;
				}
			}
			break;
		case 11:
			if(code[mc].x==0)
			{
				h2=s[t-2].i;
				h1=s[h2].i-1;
				if(h1>=s[t].i)
				{
					s[h2].i=h1;
					pc=code[mc].y;
				}
				else
					t=t-3;
			}
			else
			{
				h2=s[t-2].i;
				r1=s[h2].r-1.0;
				if(r1>=s[t].r)
				{
					s[h2].r=r1;
					pc=code[mc].y;
				}
				else
					t=t-3;
			}
			break;
		case 12:		// mark stack
			h1=btab[tab[code[mc].y].ref].vsize;
			if(t>stacksize-h1)
				ps=stkchk;
			else
			{
				t=t+5;
				s[t-1].i=h1-1;
				s[t].i=code[mc].y;
			}
			break;
		case 13:
			h1=t-code[mc].y;
			h2=s[h1+4].i;
			h3=tab[h2].lev;
			display[h3+1]=h1;
			h4=s[h1+3].i+h1;
			s[h1+1].i=pc;
			s[h1+2].i=display[h3];
			s[h1+3].i=b;
			for(h3=t+1;h3<=h4;h3++)
				s[h3].i=0;
			b=h1;
			t=h4;
			pc=tab[h2].adr;
			break;
		case 14:
			h1=tab[code[mc].y].ref-1;
			h2=0;
			h3=s[t].i;
			if(h3<h2)
				ps=inxchk;
			else if(h3>h1)
				ps=inxchk;
			else
			{
				t=t-1;
				s[t].i=s[t].i+(h3-h2);
			}
			break;
		case 15:
			h1=s[t].i;
			t=t-1;
			h2=code[mc].y+t;
			if(h2>stacksize)
				ps=stkchk;
			else
			{
				while(t<h2)
				{
					t=t+1;
					s[t]=s[h1];
					h1=h1+1;
				}
			}
			break;
		case 16:
			h1=s[t-1].i;
			h2=s[t].i;
			h3=h1+code[mc].y;
			while(h1<h3)
			{
				s[h1]=s[h2];
				h1=h1+1;
				h2=h2+1;
			}
			t=t-2;
			break;
		case 17:
			t=t+1;
			if(t>stacksize)
				ps=stkchk;
			else
				s[t].i=code[mc].y;
			break;
		case 18:
			t=t+1;
			if(t>stacksize)
				ps=stkchk;
			else
				s[t].r=rconst[code[mc].y];
			break;
		case 19:
			h1=t-code[mc].y;
			s[h1].r=s[h1].i;
			break;
		case 20:
			if(code[mc].y==1)
				scanf("%d",&s[s[t].i].i);
			else if(code[mc].y==2)
				scanf("%f",&s[s[t].i].r);
			else if(code[mc].y==3)
			{
				//scanf("%c",&s[s[t].i].c);
				while(1)
				{
					ch=getchar();
					if(ch>='0'&&ch<='9' || ch>='a'&&ch<='z' || ch>='A'&&ch<='Z')
						break;
				}
				s[s[t].i].i=ch;
			}
			t=t-1;
			break;
		case 21:
			h1=s[t].i;
			h2=code[mc].y;
			t=t-1;
			chrcnt=chrcnt+h1;
			if(chrcnt>lineleng)
				ps=lngchk;
			do{
				printf("%c",stab[h2]);
				fprintf(fout,"%c",stab[h2]);
				h1=h1-1;
				h2=h2+1;
			}while(h1!=0);
			break;
		case 22:
			chrcnt=chrcnt+fld[code[mc].y];
			if(chrcnt>lineleng)
				ps=lngchk;
			else
			{
				if(code[mc].y==1)
				{
					printf("%d\n",s[t].i);
					fprintf(fout,"%d\n",s[t].i);
				}
				else if(code[mc].y==2)
				{
					printf("%f\n",s[t].r);
					fprintf(fout,"%f\n",s[t].r);
				}
				else if(code[mc].y==3)
				{
					printf("%c\n",s[t].c);
					fprintf(fout,"%c\n",s[t].c);
				}
			}
			t=t-1;
			break;
		case 23:
			ps=fine;
			break;
		case 24:
			t=b-1;
			pc=s[b+1].i;
			b=s[b+3].i;
			break;
		case 25:
			t=b;
			pc=s[b+1].i;
			b=s[b+3].i;
			break;
		case 26:
			s[t]=s[s[t].i];
			break;
		case 27:
			s[s[t-1].i]=s[t];
			t=t-2;
			break;
		case 7:
			switch(code[mc].y)
			{
			case 0:
				t=t-1;
				if(s[t].r==s[t+1].r)
					s[t].b=true;
				else
					s[t].b=false;
				break;
			case 1:
				t=t-1;
				if(s[t].r!=s[t+1].r)
					s[t].b=true;
				else
					s[t].b=false;
				break;
			case 2:
				t=t-1;
				if(s[t].r<s[t+1].r)
					s[t].b=true;
				else
					s[t].b=false;
				break;
			case 3:
				t=t-1;
				if(s[t].r<=s[t+1].r)
					s[t].b=true;
				else
					s[t].b=false;
				break;
			case 4:
				t=t-1;
				if(s[t].r>s[t+1].r)
					s[t].b=true;
				else
					s[t].b=false;
				break;
			case 5:
				t=t-1;
				if(s[t].r>=s[t+1].r)
					s[t].b=true;
				else
					s[t].b=false;
				break;
			case 6:
				t=t-1;
				if(s[t].i==s[t+1].i)
					s[t].b=true;
				else
					s[t].b=false;
				break;
			case 7:
				t=t-1;
				if(s[t].i!=s[t+1].i)
					s[t].b=true;
				else
					s[t].b=false;
				break;
			case 8:
				t=t-1;
				if(s[t].i<s[t+1].i)
					s[t].b=true;
				else
					s[t].b=false;
				break;
			case 9:
				t=t-1;
				if(s[t].i<=s[t+1].i)
					s[t].b=true;
				else
					s[t].b=false;
				break;
			case 10:
				t=t-1;
				if(s[t].i>s[t+1].i)
					s[t].b=true;
				else
					s[t].b=false;
				break;
			case 11:
				t=t-1;
				if(s[t].i>=s[t+1].i)
					s[t].b=true;
				else
					s[t].b=false;
				break;
			case 12:
				t=t-1;
				s[t].i=s[t].i+s[t+1].i;
				break;
			case 13:
				t=t-1;
				s[t].i=s[t].i-s[t+1].i;
				break;
			case 14:
				t=t-1;
				s[t].r=s[t].r+s[t+1].r;
				break;
			case 15:
				t=t-1;
				s[t].r=s[t].r-s[t+1].r;
				break;
			case 16:
				t=t-1;
				s[t].i=s[t].i*s[t+1].i;
				break;
			case 17:
				t=t-1;
				if(s[t+1].i==0)
					ps=divchk;
				else
					s[t].i=s[t].i/s[t+1].i;
				break;
			case 18:
				t=t-1;
				s[t].r=s[t].r*s[t+1].r;
				break;
			case 19:
				t=t-1;
				s[t].r=s[t].r/s[t+1].r;
				break;
			case 20:
				s[t].i=-s[t].i;
				break;
			default:
				printf("error!");
			}
			break;
		default:
			printf("error!");
		}
	}while(ps==run&&mc<lc);
	if(ps!=fine)
	{
		if(ps==divchk)
			printf("warning: division by 0\n");
		else if(ps==inxchk)
			printf("warning: invalid index\n");
		else if(ps==stkchk)
			printf("warning: storage overflow\n");
		else if(ps==linchk)
			printf("warning: too much output\n");
		else if(ps==lngchk)
			printf("warning: line too long\n");
		else if(ps==redchk)
			printf("warning: reading past end of file\n");
	}
}

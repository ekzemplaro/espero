/* ----------------------------------------------------------------------- */
/*	espero.cpp

					la 12-an de julio,95
*/
/* ----------------------------------------------------------------------- */
#include	<iostream>
#include	<fstream>
#include	<iomanip>
#include	<stdio.h>
#include	<string.h>
#include	<ctype.h>
#include	<stdlib.h>

#include	"esperodef.h"

/* ----------------------------------------------------------------------- */
static	void vortaro_malfermi	();
static	void legi_vor	(const char nomo_vor[]);
static	void legi_vor_s4
	(const char vor_temp[],const int index,const int width);
static	void legi_vor_check	();
static	void skribi_log	();
static	void parser	(char	str_in[]);
static	void omit_unua_proc	(char	str_in[]);
static	void omit_proc	(char	str_in[]);
static	int verbo_participo_check (char str_in[],const int llx);
static	int verbo_check	(const char str_in[],const int ipos);
static	int participo_check_exec (const char str_in[],const int ipos);
static	int unu_check (const char str_in[]);
static	int numero_check (const char str_in[]);
static	int ascii_checkx (const char str_in[],const int mode);
static	int ascii_check_s2 (const char str_in[],const int ch_length);
static	int ascii_check_exec
	(const char str_in[],const int n_vor,char *avor,const int width);
static	int substantivo_check	(const char str_in[]);

/* ----------------------------------------------------------------------- */
char	*ad_vortaro[20];

int	n_vorto_suma;
int	n_vorto[15];
int	n_limit[15];

int	n_vorto_legita;

/* ----------------------------------------------------------------------- */
int main (int argc,char *argv[])
{
	char	str_inx[100];

	int	it;

	std::cerr << "*** espero *** la 12-an de julio, 95 ***\n";

	if (argc != 2)
		{
		std::cerr << "\t*** Skribu\n";
		std::cerr << "\t\tespero nomo\n";
		exit	(1);
		}

	std::cerr << argv[1] << " incluzivas jenajn malfacilajn vortojn\n\n";

	std::ifstream tin_file (argv[1]);

	if (tin_file.fail ())
		{
		std::cerr << "*** " << argv[1] << " ne trovig^as ***\n";
		exit	(1);
		}

	vortaro_malfermi	();

	skribi_log	();

	while	(!tin_file.eof ())
		{
		tin_file >> str_inx;

		if (tin_file.eof ())
			{
			break;
			}

		parser	(str_inx);
		n_vorto_legita++;
		}


	for (it=0; it<13; it++)
		{
		delete	ad_vortaro[it];
		}

	std::cerr << "\n\t\t" << n_vorto_legita << " vortoj\n";
	std::cerr << "\n*** espero *** fino ***\n";

	return	(0);
}

/* ----------------------------------------------------------------------- */
/* [2]: */
static	void vortaro_malfermi	()
{
	char	nomo_vor[50];

	int	it;

	std::ifstream tin_file ("vortaro");

	if (tin_file.fail ())
		{
		std::cerr << "*** vortaro ne trovig^as ***\n";
		exit	(1);
		}

	n_vorto_suma = 0;

	for (it=0; it<15; it++)
		{
		n_vorto[it] = 0;
		}

	n_limit[0] =	N_MAX_A;
	n_limit[1] =	N_MAX_B;
	n_limit[2] =	N_MAX_C;
	n_limit[3] =	N_MAX_D;
	n_limit[4] =	N_MAX_E;
	n_limit[5] =	N_MAX_F;
	n_limit[6] =	N_MAX_G;
	n_limit[7] =	N_MAX_H;
	n_limit[8] =	N_MAX_I;
	n_limit[9] =	N_MAX_J;
	n_limit[10] =	N_MAX_K;
	n_limit[11] =	N_MAX_L;
	n_limit[12] =	N_MAX_M;

	for (it=0; it<11; it++)
		{
		ad_vortaro[it] = new char[n_limit[it] * (it+2)];
		}

	ad_vortaro[11] = new char[N_MAX_L * L_SIZE];
	ad_vortaro[12] = new char[N_MAX_M * M_SIZE];

	while	(!tin_file.eof ())
		{
		tin_file >> nomo_vor;

		if (tin_file.eof ())
			{
			break;
			}

		legi_vor	(nomo_vor);
		}

	n_vorto_legita = 0;
}

/* ----------------------------------------------------------------------- */
/* [2-4]: */
static	void legi_vor	(const char nomo_vor[])
{
	int	ch_length;

	char	vor_temp[40];

	std::ifstream tin_file (nomo_vor);

	if (tin_file.fail ())
		{
		std::cerr << "*** " << nomo_vor << " ne trovig^as ***\n";
		exit	(1);
		}

	while	(!tin_file.eof ())
		{
		tin_file >> vor_temp;

		if (tin_file.eof ())
			{
			break;
			}

		ch_length = strlen	(vor_temp);

		if (ch_length < K_SIZE)
			{
			legi_vor_s4	(vor_temp,ch_length-1,ch_length+1);
			}
		else if (ch_length < L_SIZE)
			{
			legi_vor_s4	(vor_temp,11,L_SIZE);
			}
		else
			{
			legi_vor_s4	(vor_temp,12,M_SIZE);
			}

		n_vorto_suma++;

		legi_vor_check	();
		}
}

/* ----------------------------------------------------------------------- */
/* [2-4-4]: */
static	void legi_vor_s4 (const char vor_temp[],const int index,const int width)
{
	char	*ch_v;

	ch_v = ad_vortaro[index];

	ch_v = ch_v + n_vorto[index] * width;

	strcpy (ch_v,vor_temp);

	n_vorto[index]++;
}

/* ----------------------------------------------------------------------- */
/* [2-4-8]: */
static	void legi_vor_check	()
{
	int	it;

	for (it=0; it<12; it++)
		{
		if (n_limit[it] < n_vorto[it])
			{
			std::cerr <<  "n_vorto[" << it;
			std::cerr << "] = " << n_vorto[it] << '\n';
			std::cerr <<	"*** La vortaro estas tro granda ***\n";
			exit	(1);
			}
		}
}

/* ----------------------------------------------------------------------- */
/* [4]: */
static	void skribi_log	()
{
	double	percent[15];
	double	t1;
	double	t2;

	int	it;

	std::ofstream tfile ("espero.log");

	tfile << std::resetiosflags (std::ios::left)
			<< std::setiosflags (std::ios::fixed)
			<< std::setiosflags (std::ios::right)
		<< std::setprecision(1);

	for (it=0; it<13; it++)
		{
		t1 = n_vorto[it];
		t2 = n_limit[it];
		percent[it] = t1 / t2 * 100.0;
		}

	for (it=0; it<11; it++)
		{
		tfile << "( " << it+1 << " ) = " << n_vorto[it];
		tfile << "\t<= " << n_limit[it] << "\t\t";

		tfile << percent[it] << " %\n";
		}

	tfile << "(12 ~ 15) = " << n_vorto[11] << "\t<= " << n_limit[11];
	tfile << "\t\t" ;
	tfile << percent[11] << " %\n";
	tfile << "(16 ~ 31) = " << n_vorto[12] << "\t<= " << n_limit[12];
	tfile << "\t\t" << percent[12] << " %\n";
	tfile << "   sumo   = " << n_vorto_suma << "\n\n";
}

/* ----------------------------------------------------------------------- */
/* [6]: */
static	void parser	(char	str_in[])
{
	char	str_tmp[100];

	int	mode;
	int	flag;
	int	ll;

	mode = 0;

	switch	(str_in[0])
		{
		case	'\"':
		case	'\'':
		case	'(':
			omit_unua_proc	(str_in);
			break;

		default:
			break;
		}

	omit_proc	(str_in);

	ll = strlen	(str_in);

	flag = 0;

	if (2 < ll)
		{
		flag = verbo_participo_check	(str_in,ll);
		}

	if (flag == 0)
		{
		if (ll == 1)
			flag = unu_check	(str_in);
		else if (('0' <= str_in[0]) && (str_in[0] <= '9'))
			flag = numero_check	(str_in);
		else
			flag = ascii_checkx	(str_in,mode);
		}

	if (flag == 0)
		{
		if (('A' <= str_in[0]) && (str_in[0] <= 'Z'))
			{
			strcpy	(str_tmp,str_in);

			ll = strlen	(str_tmp);

			if (str_tmp[ll-1] == 'n')
				{
				str_tmp[ll-1] = '\0';
				flag = ascii_checkx	(str_tmp,mode);
				}

			if (flag == 0)
				{
				strcpy	(str_tmp,str_in);
				str_tmp[0] = str_tmp[0] + 0x20;
				flag = ascii_checkx	(str_tmp,mode);

				if (flag == 0)
					flag = substantivo_check (str_tmp);
				}
			}
		else
			{
			flag = substantivo_check	(str_in);
			}
		}

	if (flag == 0)
		{
		std::cout << str_in << '\n';
		}
}

/* ----------------------------------------------------------------------- */
/* [6-2]: */
static	void omit_unua_proc	(char	str_in[])
{
	int	llx;

	int	it;

	llx = strlen	(str_in);

	if (1 < llx)
		{
		for (it=0; it < llx; it++)
			str_in[it] = str_in[it+1];
		}
}

/* ----------------------------------------------------------------------- */
/* [6-3]: */
static	void omit_proc	(char	str_in[])
{
	int	llx;

	int	fino_flag;

	fino_flag = 1;

	do
		{
		llx = strlen	(str_in);

		if (llx <=1)
			break;

		switch	(str_in[llx-1])
			{
			case	'\"':
			case	'\'':
			case	'.':
			case	',':
			case	':':
			case	';':
			case	'?':
			case	'!':
			case	')':
				str_in[llx - 1] = '\0';
				break;

			default:
				fino_flag = 0;
				break;
			}
		}
		while (fino_flag == 1);
}

/* ----------------------------------------------------------------------- */
/* [6-4]: */
static	int verbo_participo_check (char str_in[],const int llx)
{
	int	flag;

	flag = 0;

	if (str_in[llx -1] == 's')
		{
		switch	(str_in[llx -2])
			{
			case	'i':
			case	'a':
			case	'o':
			case	'u':
				flag = verbo_check (str_in,llx - 2);
				break;

			default:
				break;
			}
		}
	else if (str_in[llx -1] == 'u')
		flag = verbo_check	(str_in,llx - 1);

	if ((flag == 0) && (5 < llx))
		{
		if ((strcmp (&str_in[llx-3],"nte") == 0) || 
			(strcmp (&str_in[llx-3],"nta") == 0))
			{
			flag = participo_check_exec	(str_in,llx - 4);
			}
		}

	if ((flag == 0) && (6 < llx))
		{
		if ((strcmp (&str_in[llx-4],"ntaj") == 0) || 
			(strcmp (&str_in[llx-4],"ntan") == 0))
			{
			flag = participo_check_exec	(str_in,llx - 5);
			}
		}

	if ((flag == 0) && (7 < llx))
		{
		if (strcmp (&str_in[llx-5],"ntajn") == 0) 
			{
			flag = participo_check_exec	(str_in,llx - 6);
			}
		}

	return	(flag);
}

/* ----------------------------------------------------------------------- */
/* [6-4-2]: */
static	int verbo_check	(const char str_in[],const int ipos)
{
	int	flag;

	int	mode;

	char	str_tmp[100];

	strcpy	(str_tmp,str_in);

	if (('A' <= str_tmp[0]) && (str_tmp[0] <= 'Z'))
		{
		str_tmp[0] = str_tmp[0] + 0x20;
		}

	str_tmp[ipos] = 'i';
	str_tmp[ipos+1] = '\0';

	mode = VERBO;

	flag = ascii_checkx	(str_tmp,mode);

	return	(flag);
}

/* ----------------------------------------------------------------------- */
/* [6-4-6]: */
static	int participo_check_exec (const char str_in[],const int ipos)
{
	int	flag;

	flag = 0;

	switch (str_in[ipos])
		{
		case	'i':
		case	'a':
		case	'o':
			flag = verbo_check (str_in,ipos);
			break;

		default:
			break;
		}

	return	(flag);
}

/* ----------------------------------------------------------------------- */
/* [6-6]: */
static	int unu_check (const char str_in[])
{
	int	flag;

	switch	(str_in[0])
		{
		case	'\"':
		case	'?':
		case	'/':
			flag = 1;
			break;

		default:
			if (('0' <= str_in[0]) && (str_in[0] <= '9'))
				flag = 1;
			else
				flag = 0;
			break;
		}

	return	(flag);
}

/* ----------------------------------------------------------------------- */
/* [6-8]: */
static	int numero_check (const char str_in[])
{
	int	flag;
	int	ll;
	int	ll_check;
	int	it;

	ll = strlen	(str_in);

	ll_check = ll;

	if ((3 <= ll) && (strcmp (&str_in[ll-2],"-a") == 0))
		{
		ll_check = ll - 2;
		}
	else if ((4 <= ll) && (strcmp (&str_in[ll-3],"-an") == 0))
		{
		ll_check = ll - 3;
		}
	else if ((4 <= ll) && (str_in[ll-3] == ':')
			&& (isdigit (str_in[ll-2]) != 0)
			&& (isdigit (str_in[ll-1]) != 0))
		{
		ll_check = ll - 3;
		}

	flag = 1;

	for (it=0; it< ll_check; it++)
		{
		if (str_in[it] < '0')
			{
			flag = 0;
			break;
			}
		else if ('9' < str_in[it])
			{
			flag = 0;
			break;
			}
		}

	return	(flag);
}

/* ----------------------------------------------------------------------- */
/* [6-10]: */
static	int ascii_checkx (const char str_in[],const int mode)
{
	int	ch_length;
	int	flag;

	ch_length = strlen	(str_in);

	flag = 0;

	if (mode == SUBSTANTIVO)
		{
		switch	(str_in[ch_length - 1])
			{
			case 'a':
			case 'e':
			case 'o':
				flag = -1;
				break;

			case 'j':
				if (str_in[ch_length - 2] == 'o')
					flag = -1;
				break;

			case 'u':
				if (str_in[ch_length - 2] == 'i')
					flag = -1;
				break;

			default:
				break;
			}
		}
	else if (mode == VERBO)
		{
		if (str_in[ch_length - 1] == 'i')
			flag = -1;
		}
	else
		flag = -1;

	if (flag == -1)
		{
		flag = 	ascii_check_s2	(str_in,ch_length);
		}

	return	(flag);
}

/* ----------------------------------------------------------------------- */
/* [6-10-2]: */
static	int ascii_check_s2 (const char str_in[],const int ch_length)
{
	int	flag;

	if (ch_length < 12)
		{
		flag = ascii_check_exec
			(str_in,n_vorto[ch_length-1],
			ad_vortaro[ch_length-1],ch_length+1);
		}
	else	if (ch_length < 16)
		{
		flag = ascii_check_exec	(str_in,n_vorto[11],
			ad_vortaro[11],L_SIZE);
		}
	else
		{
		flag = ascii_check_exec (str_in,n_vorto[12],
			ad_vortaro[12],M_SIZE);
		}

	return	(flag);
}

/* ----------------------------------------------------------------------- */
/* [6-10-2-4]: */
static	int ascii_check_exec
	(const char str_in[],const int n_vor,char *avor,const int width)
{
	int	flag;
	int	it;

	flag = 0;

	for (it=0; it<n_vor; it++)
		{
		if (strcmp (str_in,avor) == 0)
			{
			flag = 1;
			break;
			}
		avor = avor + width;
		}

	return	(flag);
}

/* ----------------------------------------------------------------------- */
/* [6-12]: */
static	int substantivo_check	(const char str_in[])
{
	int	mode;
	int	ll;
	int	flag;

	char	str_tmp[100];

	mode = 0;

	strcpy	(str_tmp,str_in);

	ll = strlen	(str_tmp);

	if (str_tmp[ll-1] == 'n')
		{
		str_tmp[ll-1] = '\0';
		mode = SUBSTANTIVO;
		}

	flag = ascii_checkx	(str_tmp,mode);

	if (flag == 0)
		{
		ll = strlen	(str_tmp);

		if (str_tmp[ll-1] == 'j')
			{
			str_tmp[ll-1] = '\0';
			mode = SUBSTANTIVO;
			flag = ascii_checkx	(str_tmp,mode);
			}
		}

	return	(flag);
}

/* ----------------------------------------------------------------------- */

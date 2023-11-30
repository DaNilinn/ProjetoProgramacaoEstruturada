#include <iostream>
#include <string.h>
#include <Windows.h>
#include <locale>

struct reg
{
	char nome[20];
	char tel[20];
	char filme[20];
	char status;
};

int tamanho(FILE *);
void cadastrar(FILE *);
void consultar(FILE *);
void excluir(FILE *);

int main()
{
	int op;
	FILE *arq;

	if ((arq = fopen("dados1.dat", "rb+")) == NULL)
	{
		if ((arq = fopen("dados1.dat", "wb+")) == NULL)
		{
			printf("\033[1;31mFalha ao abrir o arquivo!\n\033[0m");
			system("pause");
		}
	}

	do
	{
		system("CLS");
		printf("\033[1;34m\n======= LOCADORA IPANEMA ======= \n\033[0m\n");
		printf("\033[1;36m1.Alugar Filme\n\033[0m\n");
		printf("\033[1;36m2.Consultar Filmes Alugados\n\033[0m\n");
		printf("\033[1;36m3.Excluir cadastro\n\033[0m\n");
		printf("\033[1;31m4.Sair\n\033[0m\n");
		printf("\033[1;34m*Filmes Alugados:%d\n\033[0m\n", tamanho(arq));
		printf("\033[1;34mOpcao:\033[0m");
		scanf("%d", &op);
		switch (op)
		{
		case 1://cadastrar novo filme
			cadastrar(arq);
			break;
		case 2://consulta um filme e quem alugou
			consultar(arq);
			break;
		
			break;
		case 3: //exclui um cadastro de filme
			excluir(arq); 
			break;

		case 4: fclose(arq);
		}
	} while (op != 4);
}

void cadastrar(FILE *arq)
{
	reg contato;
	char confirma;
	contato.status = ' ';
	fflush(stdin);

	printf("\033[1;36mCadastrando novo cliente:\n\033[0m");
	printf("\033[1;36m\nNumero do cliente:%d\n\033[0m", tamanho(arq) + 1);
	printf("\033[1;36mNome..........:\033[0m");
	//getchar();
	gets(contato.nome);
	printf("\033[1;36mTelefone......:\033[0m");
	gets(contato.tel);
	printf("\033[1;36mFilme Escolhido........:\033[0m");
	gets(contato.filme);
	printf("\033[1;36m\nConfirma <s/n>:\033[0m");
	fflush(stdin);
	scanf("%c", &confirma);

	if (toupper(confirma) == 'S')
	{
		printf("\ngravando...\n\n");
		fseek(arq, 0, SEEK_END);
		fwrite(&contato, sizeof(reg), 1, arq);

	}
	system("pause");
}

void consultar(FILE *arq)
{
	reg contato;
	int nr;
	printf("\033[1;36m\nConsulta pelo numero de cadastro\n\033[0m");
	printf("\033[1;36m\nInforme o Codigo...:\033[0m");
	scanf("%d", &nr);
	if ((nr <= tamanho(arq)) && (nr>0))
	{
		fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
		fread(&contato, sizeof(reg), 1, arq);
		if (contato.status == ' ')
		{
			printf("\033[1;36m\nNome......:%s\033[0m", contato.nome);
			printf("\033[1;36m\nTelefone..:%s\033[0m", contato.tel);
			printf("\033[1;36m\nFilme Escolhido....:%s\n\n\033[0m", contato.filme);
		}

		else
			printf("\033[1;31m\nCadastro excluido! \n\033[0m\n");

	}
	else
	{
		printf("\033[1;31m\nNumero de cadastro invalido!\n\033[0m\n");
	}
	system("pause");
}

void excluir(FILE *arq)
{
	reg contato;
	char confirma;
	int nr;

	printf("\033[1;36m\nInforme o codigo de cadastro para excluir\n\033[0m");
	scanf("%d", &nr);
	if ((nr <= tamanho(arq)) && (nr>0))
	{
		fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
		fread(&contato, sizeof(reg), 1, arq);
		if (contato.status == ' ')
		{
			printf("\033[1;36m\nNome......:%s\033[0m", contato.nome);
			printf("\033[1;36m\nTelefone..:%s\033[0m", contato.tel);
			printf("\033[1;36m\nFilme Escolhido....:%s\n\033[0m", contato.filme);
			printf("\033[1;31m\nConfirma a exclusao: <s/n>\n\033[0m");
			getchar();
			scanf("%c", &confirma);

			if (toupper(confirma) == 'S')
			{
				printf("\033[1;31m\nexcluindo...\n\n\033[0m");
				fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
				contato.status = '*';
				fwrite(&contato, sizeof(reg), 1, arq);
			}
		}
	else
		printf("\033[1;31mCadastro inexistente! \n\033[0m\n");
	}
	else
	{
		printf("\033[1;31m\nNumero de cadastro invalido!\n\033[0m\n");
	}
	system("pause");
}

int tamanho(FILE *arq)
{
	fseek(arq, 0, SEEK_END);
	return ftell(arq) / sizeof(reg);
}

#ifndef _LABIRINTO_H_
#define _LABIRINTO_H_

typedef enum
{
	falso, verdadeiro
} boolean;


class Labirinto {
public:
	char campo;
	
	void set(char campo);

	char get();

	void show_dados();
};

#endif

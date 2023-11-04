//Enigma na 100%
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
bool zad = false;
class Wirnik
{
public:
	signed short * konfiguracja; //wirnik zapamiêtuje relacje pomiêdzy indexem (wejsciem) a wyjœciem  = i + konfiguracja[i]  ( '+' wzglêdne)
	signed short * reversedKonf; // uzywany podczas nawracania z reflectora itp
	signed short * wyzwalacze; // info kiedy sie wirnik obraca (ten nastepny) 
	signed short liczbaWyzwalaczy;
	signed short liczbaLiterAlfabetu;
	signed short indexWirnikaEnigmy;
	signed short pozycja; // nieinicjalizowana na pocz¹tku //musi byc public
	Wirnik()
	{
		signed short * konfiguracja = NULL;
		signed short * reversedKonf = NULL;
		signed short * wyzwalacze = NULL;
	}
	Wirnik(signed short liczbaLiterAlfabetu)
	{

		this->liczbaLiterAlfabetu = liczbaLiterAlfabetu;
		this->konfiguracja = (signed short *)malloc(sizeof(signed short) * liczbaLiterAlfabetu * 2); //mallocuja na raz oba + 
		this->reversedKonf = &this->konfiguracja[liczbaLiterAlfabetu]; // i sobie znajduje poczatek //na przysz³oœæ: kompilator jakims cudem monrzy razy shorta
		signed short relacja;
		for (signed short i = 0; i < liczbaLiterAlfabetu; i++)
		{
			scanf("%hd", &relacja);
			relacja--;
			this->konfiguracja[i] = relacja - i;
			this->reversedKonf[relacja] = i - relacja;

		}

		scanf("%hd", &this->liczbaWyzwalaczy);
		this->wyzwalacze = (signed short *)malloc(sizeof(signed short) * this->liczbaWyzwalaczy);
		for (signed short i = 0; i < this->liczbaWyzwalaczy; i++)
		{
			scanf("%hd", &this->wyzwalacze[i]);
			if (this->wyzwalacze[i] == 1)
				this->wyzwalacze[i] = this->liczbaLiterAlfabetu - 1;
			else
				this->wyzwalacze[i] -= 2;


		}
		this->pozycja = 0;

	}

	void initialize(signed short pozycjaStartowa, signed short indexWirnikaEnigmy)
	{
		//jeœli pocz¹tkowa pozycja tego wirnika podana jest przy pomocy ostatniej litery alfabetu pierwsza litera kodowana jest normalnie
		//ale tylko jak jest to pierwszy wirnik w enigmie!
		//w przeciwnym wypadku jest "normalnie"
		//daltego ni¿ej odejmuje wtedy 1 od pozycji
		if (indexWirnikaEnigmy)
			pozycjaStartowa--;
		if ((this->liczbaLiterAlfabetu) - pozycjaStartowa)
		{
			this->pozycja = pozycjaStartowa;
		}
		else
		{
			this->pozycja = 0;
		}
	}

	void turn()
	{
		if ((this->liczbaLiterAlfabetu - 1) - this->pozycja) //jezeli pozycja jest rowana max liczbie
		{
			this->pozycja = this->pozycja + 1;
		}
		else
		{
			this->pozycja = 0;
		}
		/*
		signed short buf;
		signed short buf2;
		signed short c1 = this->konfiguracja[this->liczbaLiterAlfabetu - 1];
		signed short c2 = this->reversedKonf[this->liczbaLiterAlfabetu - 1];
		for (signed short i = this->liczbaLiterAlfabetu - 1; i>0; i--)
		{
		buf = this->konfiguracja[i - 1];
		buf2 = this->reversedKonf[i - 1];
		this->konfiguracja[i - 1] = c1;
		this->reversedKonf[i - 1] = c2;
		c1 = buf;
		c2 = buf2;
		}
		this->konfiguracja[liczbaLiterAlfabetu - 1] = buf;
		this->reversedKonf[liczbaLiterAlfabetu - 1] = buf2;
		*/
	}
private: signed short trueIndex(signed short cyfra) // wykonuje obliczeñ indexu zamiast przesuwaæ tablicy
{
	signed short trueIndex = this->pozycja + cyfra;
	if (trueIndex >= this->liczbaLiterAlfabetu)
		return trueIndex - this->liczbaLiterAlfabetu;
	return trueIndex;
}
public:
	signed short use(signed short cyfra, bool &turn, unsigned int indexWirnikaEnigmy, bool &doubleTurn, bool &doubleEnable, bool &jestdoubleTurn)//tu gagatek nie dza³a
	{
		bool byldoubleTurn = doubleTurn;
		//czy ma siê obróciæ?
		switch (indexWirnikaEnigmy)
		{
		case 0:
			byldoubleTurn = doubleEnable;
			//sprawadzamy czy pozycja jest zgodna z wyzwalaczem
			// pierwszy obraca siê zawsze
			turn = false;
			for (signed short j = 0; j < this->liczbaWyzwalaczy; j++)
			{
				if (this->pozycja == this->wyzwalacze[j])
				{
					turn = true;
					doubleEnable = true;
					byldoubleTurn = false;
					break;
				}
			}
			if (byldoubleTurn) //ale nie by³o wyzwalacza
			{
				turn = false;
				doubleEnable = false;
				byldoubleTurn = false;
			}
			break;
		case 1:
			if (doubleTurn || doubleEnable) turn = true;
			//sprawadzamy czy pozycja jest zgodna z wyzwalaczem
			if (turn) // je¿eli ten siê obraca 
			{
				turn = false;
				for (signed short j = 0; j < this->liczbaWyzwalaczy; j++)
				{
					if (this->pozycja == this->wyzwalacze[j])
					{
						if (doubleTurn)
						{
							turn = true;
							doubleTurn = true;
							byldoubleTurn = false;
							jestdoubleTurn = false;
							break;
						}
					}
				}
				if (doubleEnable == true && turn == false)
				{
					doubleEnable = false;
					jestdoubleTurn = true;
					turn = false;
					if (!doubleTurn)
					{
						byldoubleTurn = false;
					}
					doubleTurn = true;
					break;
				}
			}
			if (byldoubleTurn) //ale nie by³o wyzwalacza
			{
				turn = false;
				doubleTurn = false;
				doubleEnable = true;
				break;
			}
			break;
		default:
			turn = false;
			break;
		}
		//odczytanie kodu
		signed short kod;
		kod = this->konfiguracja[this->trueIndex(cyfra)] + cyfra;
		if (kod >= 0 && kod <= this->liczbaLiterAlfabetu - 1)
			return kod;
		else if (kod < 0)
			return (this->liczbaLiterAlfabetu - 1) + kod + 1; // +1 bo jakby przejscie 0 -> n jest warte 1
		else //kod >= 0 && kod > this->liczbaLiterAlfabetu - 1
			return kod - (this->liczbaLiterAlfabetu - 1) - 1; // -1 bo przejscie n - > 0 jest warte 1;
	}

	signed short retract(signed short kod, bool turn, bool trueTurn, signed short indexWirnikaEnigmy, bool ostatni, bool &doubleTurn)
	{
		//dostanie wartosci
		signed short trueKod = this->reversedKonf[this->trueIndex(kod)] + kod;
		if (trueKod < 0)
			trueKod = (this->liczbaLiterAlfabetu - 1) + trueKod + 1;
		else if (trueKod > 0 && trueKod > this->liczbaLiterAlfabetu - 1)
			trueKod = trueKod - (this->liczbaLiterAlfabetu - 1) - 1;
		//obracanie
		switch (indexWirnikaEnigmy)
		{
		case 1:
			if (trueTurn == true)
			{
				this->turn();
			}
			else if (ostatni == false && turn == true)
			{
				this->turn();
			}
			break;
		case 0:
		case 2:
			if (trueTurn == true)
			{
				this->turn();
			}
			break;
		default:
			break;
		}
		return trueKod;
	}
	~Wirnik()
	{
		free(this->konfiguracja);
		free(this->wyzwalacze);
	}
	Wirnik(const Wirnik &kopiowany) 
	{
		this->konfiguracja = (signed short *)malloc(sizeof(signed short) * kopiowany.liczbaLiterAlfabetu * 2);
		this->reversedKonf = &this->konfiguracja[kopiowany.liczbaLiterAlfabetu];
		this->wyzwalacze = (signed short *)malloc(sizeof(signed short) * kopiowany.liczbaWyzwalaczy);
		for (signed short i = 0; i < kopiowany.liczbaLiterAlfabetu; i++)
		{
			this->konfiguracja[i] = kopiowany.konfiguracja[i];
			this->reversedKonf[i] = kopiowany.reversedKonf[i];
		}
		for (signed short i = 0; i < kopiowany.liczbaWyzwalaczy; i++)
		{
			this->wyzwalacze[i] = kopiowany.wyzwalacze[i];
		}
		this->liczbaWyzwalaczy = kopiowany.liczbaWyzwalaczy;
		this->liczbaLiterAlfabetu = kopiowany.liczbaLiterAlfabetu;
		this->pozycja = kopiowany.pozycja;
	}
	Wirnik operator = (Wirnik const &przypisywana)
	{
		if (this->konfiguracja != NULL)
			free(this->konfiguracja);
		if (this->wyzwalacze != NULL)
			free(this->wyzwalacze);
		this->konfiguracja = przypisywana.konfiguracja;
		this->reversedKonf = &this->konfiguracja[przypisywana.liczbaLiterAlfabetu];
		this->wyzwalacze = przypisywana.wyzwalacze;
		this->liczbaWyzwalaczy = przypisywana.liczbaWyzwalaczy;
		this->liczbaLiterAlfabetu = przypisywana.liczbaLiterAlfabetu;
		this->pozycja = przypisywana.pozycja;
		return *this;
	}
};

class Reflector
{
public:
	signed short liczbaLiterAlfabetu;
	signed short * konfiguracjaa;
	Reflector(signed short liczbaLiterAlfabetu)
	{
		this->liczbaLiterAlfabetu = liczbaLiterAlfabetu;
		this->konfiguracjaa = (signed short *)malloc(sizeof(signed short) * liczbaLiterAlfabetu);
		for (signed short i = 0; i < liczbaLiterAlfabetu; i++)
		{
			signed short buf;
			scanf("%hd", &buf);
			*(this->konfiguracjaa + i) = buf - 1;
		}
	}
	signed short use(signed short kod)
	{
		return konfiguracjaa[kod];
	}
	~Reflector()
	{
		free(konfiguracjaa);
	}
	Reflector(const Reflector &kopiowany) 
	{
		free(konfiguracjaa);
		konfiguracjaa = (signed short *)malloc(sizeof(signed short) * kopiowany.liczbaLiterAlfabetu);
		for (signed short i = 0; i < kopiowany.liczbaLiterAlfabetu; i++)
		{
			konfiguracjaa[i] = kopiowany.konfiguracjaa[i];
		}
		liczbaLiterAlfabetu = kopiowany.liczbaLiterAlfabetu;
	}
	Reflector operator = (Reflector const &przypisywana)
	{
		free(konfiguracjaa);
		konfiguracjaa = przypisywana.konfiguracjaa;
		liczbaLiterAlfabetu = przypisywana.liczbaLiterAlfabetu;
		return *this;
	}
};


class Enigma
{
public:
	signed short liczbaWirnikowEnigmy;
	signed short liczbaLiterAlfabetu; //do testów
	Wirnik ** wirnikiEnigmy;
	Reflector * reflectorEnigmy;
	bool doubleTurn;
	bool doubleEnable;
	bool jestdoubleTurn;
	Enigma(Wirnik ** wirniki, Reflector ** reflectory, signed short liczbaLiterAlfabetu)
	{
		this->liczbaLiterAlfabetu = liczbaLiterAlfabetu;
		scanf("\n%hd", &liczbaWirnikowEnigmy);
		wirnikiEnigmy = (Wirnik **)malloc(sizeof(Wirnik **) * liczbaWirnikowEnigmy);
		for (signed short i = 0; i < liczbaWirnikowEnigmy; i++)
		{
			signed short indexObecnegoWirnika;
			signed short pozycjaPoczatkowa;
			scanf("%hd", &indexObecnegoWirnika);//czy nie powinienem zapisac indexu do wirnika
			scanf("%hd", &pozycjaPoczatkowa); // jezeli wirnik istnieje //test
			Wirnik * nowyWirnik = new Wirnik(*wirniki[indexObecnegoWirnika]);//kopiuje
			wirnikiEnigmy[i] = nowyWirnik;
			wirnikiEnigmy[i]->initialize(pozycjaPoczatkowa, i); // -1 boo jest przesuniete o jeden 1 to nic nie rob
		}
		signed short indexReflectora;
		scanf("%hd", &indexReflectora);
		reflectorEnigmy = reflectory[indexReflectora]; 
		doubleTurn = false;
		doubleEnable = false;
		jestdoubleTurn = false;
	}
	void szyfruj()
	{
		signed short cyfra;
		while (true)
		{
			scanf("%hd", &cyfra);
			switch (cyfra)
			{
			case 0:
				return;
				break;
			default:
				cyfra--; // by znormalizowaæ o 1 (by siêtablice ³adne zapisywa³y //test
				cyfra = szyfrujCyfre(0, true, cyfra);
				printf("%hd ",(signed short) cyfra + 1);
				break;
			}
		}
	}
	signed short szyfrujCyfre(signed short indexWirnikaEnigmy, bool turn, signed short cyfra)
	{
		//:)
		bool trueTurn = turn;
		if (indexWirnikaEnigmy < liczbaWirnikowEnigmy - 1)
		{
			cyfra = wirnikiEnigmy[indexWirnikaEnigmy]->use(cyfra, turn, indexWirnikaEnigmy, doubleTurn, doubleEnable, jestdoubleTurn);
			cyfra = szyfrujCyfre(indexWirnikaEnigmy + 1, turn, cyfra);
			cyfra = wirnikiEnigmy[indexWirnikaEnigmy]->retract(cyfra, turn, trueTurn, indexWirnikaEnigmy, false, doubleTurn);//pamietac o double turn
		}
		else if (indexWirnikaEnigmy == liczbaWirnikowEnigmy - 1)
		{
			cyfra = wirnikiEnigmy[indexWirnikaEnigmy]->use(cyfra, turn, indexWirnikaEnigmy, doubleTurn, doubleEnable , jestdoubleTurn);
			cyfra = reflectorEnigmy->use(cyfra);
			cyfra = wirnikiEnigmy[indexWirnikaEnigmy]->retract(cyfra, turn, trueTurn, indexWirnikaEnigmy, true, doubleTurn);//pamietac o double turn
		}
		//zwracam kod:
		return cyfra;
	}
	~Enigma()
	{
		for (signed short i = 0; i < liczbaWirnikowEnigmy; i++)
		{
			delete(wirnikiEnigmy[i]);
		}
		free(wirnikiEnigmy);
	}
	Enigma(const Enigma &kopiowany) // jest tu by nie bylo warninga
	{
		free(wirnikiEnigmy);
		wirnikiEnigmy = (Wirnik **)malloc(sizeof(Wirnik **) * kopiowany.liczbaWirnikowEnigmy);
		for (signed short i = 0; i < kopiowany.liczbaWirnikowEnigmy; i++)
		{
			wirnikiEnigmy[i] = kopiowany.wirnikiEnigmy[i];
		}
		liczbaWirnikowEnigmy = kopiowany.liczbaWirnikowEnigmy;
		reflectorEnigmy = kopiowany.reflectorEnigmy;
	}
	Enigma operator = (Enigma const &przypisywana)
	{
		free(wirnikiEnigmy);
		liczbaWirnikowEnigmy = przypisywana.liczbaWirnikowEnigmy;
		wirnikiEnigmy = przypisywana.wirnikiEnigmy;
		reflectorEnigmy = przypisywana.reflectorEnigmy;
		return *this;
	}
};


int main()
{
	signed short wirnikiLiczba = 0;
	signed short reflektoryLiczba = 0;
	signed short liczbaLiterAlfabetu = 0;
	signed short liczbaZadan = 0;

	Wirnik ** wirniki;
	Reflector ** reflectory;
	
	//przyjmowanie danych instrukcji
	//wirniki
	scanf("%hd", &liczbaLiterAlfabetu);
	scanf("%hd", &wirnikiLiczba);
	wirniki = (Wirnik **)malloc(sizeof(Wirnik **) * wirnikiLiczba);
	for (signed short i = 0; i < wirnikiLiczba; i++)
	{
		wirniki[i] = new Wirnik(liczbaLiterAlfabetu);
	}
	//reflectory
	scanf("%hd", &reflektoryLiczba);
	reflectory = (Reflector **)malloc(sizeof(Reflector **) * reflektoryLiczba);
	for (signed short i = 0; i < reflektoryLiczba; i++)
	{
		reflectory[i] = new Reflector(liczbaLiterAlfabetu);
	}
	//przyjmowanie danych szyfru
	scanf("\n%hd", &liczbaZadan);
	Enigma * zadanie;
	for (signed short i = 0; i < liczbaZadan; i++)
	{
		zadanie = new Enigma(wirniki, reflectory, liczbaLiterAlfabetu);
		zadanie->szyfruj();
		delete(zadanie);
		printf("\n");
	}
	//dealokacja pamiêci
	for (signed short i = 0; i < wirnikiLiczba; i++)
	{
		delete(wirniki[i]);
	}
	free(wirniki);
	for (signed short i = 0; i < reflektoryLiczba; i++)
	{
		
		delete(reflectory[i]);
	}
	free(reflectory);
}
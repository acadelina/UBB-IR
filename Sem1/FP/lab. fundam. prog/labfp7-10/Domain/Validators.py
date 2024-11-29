from Domain.Client import *
from Domain.Film import *
from Exceptions.Exc import *



def check_cnp(client):
    '''

    :param client:
    :return:
    '''
    c_cnp = client.getCnp()

    if len(c_cnp) != 13:
        return 0
    if c_cnp[0] not in ['1', '2', '5', '6']:
        return 0
    if int(c_cnp[1] + c_cnp[2]) < 0 or int(c_cnp[1] + c_cnp[2]) > 99:
        return 0
    if int(c_cnp[3] + c_cnp[4]) < 0 or int(c_cnp[3] + c_cnp[4]) > 12:
        return 0
    if int(c_cnp[5] + c_cnp[6]) < 0 or int(c_cnp[5] + c_cnp[6]) > 31:
        return 0

    return 1


class ValidatorFilm(object):

    def validate(self, film):
        '''
        Verifica parametrii, daca 1 sau mai multi sunt invalizi ---> ValidationError
        :param film:
        :return:
        '''
        gen_ok = ["Comedy","Thriller","Horror","Action","Animation","Drama","Musical","Romance","Fantasy","SF","altele"]
        erori = ""
        if film.getId()<0:
            erori += "id invalid!\n"
        if film.getTitlu()=="":
            erori += "titlu invalid!\n"
        if film.getDesc()=="":
            erori += "descriere invalida!\n"
        if film.getGen() not in gen_ok:
            erori += "gen invalid!\n"

        if len(erori)>0:
            raise ValidationException(erori)

class ValidatorClient(object):

    def validate(self, client):
        '''
        Verifica parametrii, daca 1 sau mai multi sunt invalizi ---> ValidationError
        :param film:
        :return:
        '''
        
        erori = ""
        if int(client.getId())< 0:
            erori += "id invalid!\n"
        if client.getNume() == "":
            erori += "nume invalid!\n"
        if client.getCnp() == "":
            erori += "CNP invalid!\n"
        elif len(client.getCnp()) !=13:
            erori += "CNP invalid!\n"


        if len(erori) > 0:
            raise ValidationException(erori)
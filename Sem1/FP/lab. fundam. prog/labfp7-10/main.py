from Domain.Validators import *
from Repsitory.Film import *
from Repsitory.Client import *
from Repsitory.Inchirieri import*
from Service.Inchirieri import *
from Service.Client import *
from Service.Film import*
from UI.Console import *




repo_file_film=filmFileRepo('data/filme.txt')
val_filme=ValidatorFilm()
serv_film=FilmService(repo_file_film,val_filme)

repo_file_client=ClientFileRepo('data/clienti.txt')
val_client=ValidatorClient()
serv_clienti=ClientService(repo_file_client,val_client)

repo_inchirieri=inchiriereRepoFile('data/inchirieri.txt')
serv_inchirieri=InchiriereService(repo_inchirieri,repo_file_film,repo_file_client)

ui=Console(serv_film,serv_clienti,serv_inchirieri)
ui.ui()
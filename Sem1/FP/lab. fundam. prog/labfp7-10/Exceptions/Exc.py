class ShowManagerException(Exception):
    pass


class ValidationException(ShowManagerException):
    def __init__(self, msgs):
        """
        :param msgs: lista de mesaje de eroare
        :type msgs: msgs
        """
        self.__err_msgs = msgs

    def getMessages(self):
        return self.__err_msgs

    def __str__(self):
        return 'Validation Exception: ' + str(self.__err_msgs)


class RepositoryException(ShowManagerException):
    def __init__(self, msg):
        self.__msg = msg

    def getMessage(self):
        return self.__msg

    def __str__(self):
        return 'Repository Exception: ' + str(self.__msg)
class GenException(ValidationException):
    def __init__(self):
        ValidationException.__init__(self,"Genul dat nu este valid.")
class IDException(ValidationException):
    def __init__(self):
        ValidationException.__init__(self,"ID-ul trebuie sa fie un numar intreg")
class CNPException(ValidationException):
    def __init__(self):
        ValidationException.__init__(self,"CNP-ul trebuie sa fie un numar intreg de 13 cifre")
class DuplicateIDException(RepositoryException):
    def __init__(self):
        RepositoryException.__init__(self, "ID duplicat.")


class RentalAlreadyAssignedException(RepositoryException):
    def __init__(self):
        RepositoryException.__init__(self, "Inchiriere existent deja pentru filmul si clientul dat.")


class FilmNotFoundException(RepositoryException):
    def __init__(self):
        RepositoryException.__init__(self, "Filmul nu a fost gasit.")


class RentalNotFoundException(RepositoryException):
    def __init__(self):
        RepositoryException.__init__(self, "Inchirierea nu a fost gasita.")



class ClientNotFoundException(RepositoryException):
    def __init__(self):
        RepositoryException.__init__(self, "Clientul nu a fost gasit.")


class NotEnoughRatingsException(ShowManagerException):
    def __init__(self):
        pass


class CorruptedFileException(ShowManagerException):
    def __init__(self):
        pass

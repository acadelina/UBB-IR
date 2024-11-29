class Emisiune:
   def  __init__(self,nume,tip,durata,descriere):
      self.__nume=nume
      self.__tip=tip
      self.__durata=durata
      self.__descriere=descriere

   def get_em_nume(self):
      return self.__nume
   
   def get_em_tip(self):
      return self.__tip
   
   def get_em_durata(self):
      return self.__durata
   
   def get_em_descriere(self):
      return self.__descriere
   
   def set_em_nume(self,nou):
      self.__nume=nou

   def set_em_tip(self,nou):
      self.__tip=nou

   def set_em_durata(self,nou):
      self.__durata=nou

   def set_em_descriere(self,nou):
      self.__descriere=nou
   def __equ__(self,other):
      return self.__nume == other.get_nume() and self.__tip== other.get_tip()
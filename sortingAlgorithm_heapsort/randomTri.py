#! /usr/bin/python
# -*- coding: utf-8 -*-

import os
import sys
import re

from random import *


#******************************************************************************************************************
# Fonction de création de tableau de tailles différentes, triés ou non dans l'ordre croissant ou décroissant 
#******************************************************************************************************************
def createTableau(size,param) :
    liste = sample(xrange(10000), size)
    if param == "decroissant" :        
        output = open("tableau.tmp","w")
        for elt in sorted(liste,reverse=True) :
            output.write(str(elt)+"\n")
        output.close()
    elif param == "croissant" :        
        output = open("tableau.tmp","w")
        for elt in sorted(liste,reverse=False) :
            output.write(str(elt)+"\n")
        output.close()
    elif param == "random" :        
        output = open("tableau.tmp","w")
        for elt in liste :
            output.write(str(elt)+"\n")
        output.close()
    else :
        print "error : bad parameter"
        sys.exit()
        
# 5 tailles de fichiers d'entiers choisis pour les tests
sizeList = [50,100,250,500,1000] 
# Création d'un dictionnaire pour afficher les boxplot dans un ordre croissant de taille de fichier d'entrée
sizeToGgplot = {50:'a-50', 100:'b-100', 250:'c-250', 500:'d-500', 1000:'e-1000'}


#******************************************************************************************************************
# Fonction de création de tableau de tailles différentes, triés ou non dans l'ordre croissant ou décroissant 
#******************************************************************************************************************
# Création du fichier contenant les temps d'exécution et la taille du tableau
outputStat = open("stats.txt","w")
outputStat.write("time\tsize\tparameter\n") # En-tête

for size in sizeList :
    for parameter in ["random","decroissant","croissant"] :
        for n in xrange(1,1000) : # Création de 1 000 tableaux de taille 50, 100, etc. entiers


            createTableau(size,parameter)

            # Lance le script de tri par tas avec les paramètres requis : nom du fichier contenant les entiers et nom du fichier de sortie
            cmd = "./triTas tableau.tmp sortie.tmp > time.tmp"
            #print cmd
            os.system(cmd)

            file = open("time.tmp","r")
            for line in file :
                time = int(line.rstrip())
                outputStat.write(str(time)+"\t"+str(sizeToGgplot[size])+"\t"+parameter+"\n")
            file.close()

            cmd = "rm *.tmp"
            os.system(cmd)



#**********************************************************
# Lance le script R pour la génération de boxplot
#**********************************************************
outputStat.close()
cmd = "./stat.r"
os.system(cmd)

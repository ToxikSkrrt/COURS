#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Mar 25 17:11:27 2020

@author: cgenial
"""
import matplotlib.pyplot as plt
    #Les fonctions------------------------------------------------------
def calcul_vitesses(abscisses,ordonnees,temps):
        v_x=[]
        v_y=[]
        for n in range(len(abscisses)-1):
            v_x.append((abscisses[n+1]-abscisses[n])/(temps[n+1]-temps[n]))
            v_y.append((ordonnees[n+1]-ordonnees[n])/(temps[n+1]-temps[n]))
        temps=temps[:-1]
        return v_x,v_y,temps
def representation_graphique(abscisses,ordonnees,v_x,v_y):
        plt.figure(figsize=(10,3))
        plt.subplots_adjust(left=0.06, bottom=0.16, right=0.99, top=0.92,
                    wspace=0.2, hspace=None)
        #------------------------------
        plt.subplot(1,3,1)
        plt.scatter(abscisses,ordonnees,marker='+')
        plt.title('Vecteur vitesse instantannée')
        plt.xlabel('x en (m)')
        plt.ylabel('Altitude z en (m)')
        plt.xlim(0.8*min(abscisses),1.2*max(abscisses))
        for i in range(0,len(v_x),1):
            V=plt.quiver(abscisses[i], ordonnees[i] ,v_x[i] , v_y[i],
             scale_units='xy',angles='xy', scale=12)
            plt.quiverkey(V,0.8,0.8,500,label='v')
        #------------------------------
        plt.subplot(1,3,2)
        plt.scatter(abscisses,ordonnees,marker='+')
        plt.title('Variation du vecteur vitesse')
        plt.xlabel('x en (m)')
        plt.ylabel('Altitude z en (m)')
        plt.xlim(0.8*min(abscisses),1.2*max(abscisses))
        for i in range(1,len(v_x),1):
            DV=plt.quiver(abscisses[i],ordonnees[i],v_x[i]-v_x[i-1],v_y[i]-v_y[i-1],
            scale_units='xy',angles='xy', scale=2, color='red')
            plt.quiverkey(DV,0.8,0.8,100,label='V(n)-V(n-1)', labelcolor='red')
        #-------------------------------
        plt.subplot(1,3,3)
        plt.scatter(abscisses,ordonnees,marker='+')
        plt.title('Somme des forces extérieures')
        plt.xlabel('x en (m)')
        plt.ylabel('Altitude z en (m)')
        plt.xlim(0.8*min(abscisses),1.2*max(abscisses))
        for i in range(1,len(v_x),1):
            F=plt.quiver(abscisses[i],ordonnees[i],0,-0.06*9.8,
            scale_units='xy',angles='xy', scale=1, color='g')
            plt.quiverkey(F,0.8,0.8,50,label='F', labelcolor='g')
        #-------------------------------
        plt.show()
    #Le programme principal--------------------------------------------
x=[0.00,0.50,1.00,1.50,2.00,2.50,3.00,3.50,4.00,4.50,5.00]
z=[5.00,4.95,4.80,4.56,4.22,3.77,3.23,2.60,1.86,1.03,0.09]
t=[0.00,0.10,0.20,0.30,0.40,0.50,0.60,0.70,0.80,0.90,1.00]
v_x,v_y,temps_v=calcul_vitesses(x,z,t)
representation_graphique(x,z,v_x,v_y)
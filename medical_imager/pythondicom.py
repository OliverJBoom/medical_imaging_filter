# -*- coding: utf-8 -*-
"""
Created on Tue Feb  5 11:53:08 2019

@author: Hamed
"""
import os
import pydicom
import matplotlib.pyplot as plt

ds = pydicom.dcmread("DICOM/000001.dcm")

plt.imshow(ds.pixel_array[10:400, 10:400], cmap=plt.cm.bone)

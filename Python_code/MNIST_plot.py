import numpy as np
import struct as st

filename = {'images': 'train-images.idx3-ubyte', 'labels': 'train-labels.idx1-ubyte'}
train_imagesfile = open(filename['images'], 'rb')

"""-----------------------------------in / out learn img----------------------------------------"""

#  put pointer to the file start.
train_imagesfile.seek(0)

#  read only 4 bytes (they determine properties of deta in file: matrices rows, columns...)
magic = st.unpack('>4B', train_imagesfile.read(4))

#num of images
Img = st.unpack('>I',train_imagesfile.read(4))[0]
#num of rows
nR = st.unpack('>I',train_imagesfile.read(4))[0]
#num of column
nC = st.unpack('>I',train_imagesfile.read(4))[0]

images_array = np.zeros((Img,nR,nC))

#since each pixel data is 1 byte
nBytesTotal = Img*nR*nC*1
images_array = np.asarray(st.unpack('>'+'B'*nBytesTotal, train_imagesfile.read(nBytesTotal))).reshape((Img,nR,nC))

output = open('C://Users//Le//Desktop//NurealNW//BackPropagation//C_code//img_10000.txt', 'w')
for i in range(0, 60000, 1):
    output.write('\n')
    for j in range(0, 28, 1):
        output.write('\n')
        for k in range(0, 28, 1):
            output.write(str(int(images_array[i][j][k])/256) + ' ')
output.close()

"""-----------------------------------in / out learn lab----------------------------------------"""

train_lable = open(filename['labels'], 'rb')
magic_lable = st.unpack('>4B', train_lable.read(4))
#num of labels
Lbl = st.unpack('>I',train_lable.read(4))[0]

lables_array = np.zeros(Lbl)
lables_array = np.asarray(st.unpack('>'+'B'*Lbl, train_lable.read(Lbl)))
output_lable = open('C://Users//Le//Desktop//NurealNW//BackPropagation//C_code//lab_10000.txt', 'w')

output_lable.write('\n')
for i in range(0, 60000, 1):
    output_lable.write(str(int(lables_array[i])) + ' ')
output_lable.close()

"""-----------------------------------in / out test img----------------------------------------"""

test_filename = {'images': 't10k-images.idx3-ubyte', 'labels': 't10k-labels.idx1-ubyte'}
test_images_file = open(test_filename['images'], 'rb')

test_images_file.seek(0)
test_magic = st.unpack('>4B', test_images_file.read(4))

test_Img = st.unpack('>I',test_images_file.read(4))[0]
test_nR = st.unpack('>I',test_images_file.read(4))[0]
test_nC = st.unpack('>I',test_images_file.read(4))[0]

test_images_array = np.zeros((test_Img,test_nR,test_nC))

test_nBytesTotal = test_Img*test_nR*test_nC*1
test_images_array = np.asarray(st.unpack('>'+'B'*test_nBytesTotal, test_images_file.read(test_nBytesTotal))).reshape((test_Img,test_nR,test_nC))

test_output = open('C://Users//Le//Desktop//NurealNW//BackPropagation//C_code//img_test.txt', 'w')
for i in range(0, 10000, 1):
    test_output.write('\n')
    for j in range(0, 28, 1):
        test_output.write('\n')
        for k in range(0, 28, 1):
            test_output.write(str(int(test_images_array[i][j][k])/256) + ' ')
test_output.close()

"""-----------------------------------in / out test lab----------------------------------------"""

test_lable = open(test_filename['labels'], 'rb')
magic_lable = st.unpack('>4B', test_lable.read(4))
Lbl = st.unpack('>I',test_lable.read(4))[0] #num of lables

lables_array = np.zeros(Lbl)
lables_array = np.asarray(st.unpack('>'+'B'*Lbl, test_lable.read(Lbl)))
output_lable = open('C://Users//Le//Desktop//NurealNW//BackPropagation//C_code//lab_test.txt', 'w')

output_lable.write('\n')
for i in range(0, 10000, 1):
    output_lable.write(str(int(lables_array[i])) + ' ')
output_lable.close()

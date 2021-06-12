Step 1.</br>
Before run compile those projects MessageInterface, NetCode</br>
</br>
copy: libMessageInterface.so from MessageInterface project</br>
copy: libNetCode.so from NetCode/Output project</br>
</br>
and paste into this folder (UdpClient)</br>
</br>
Step 2.</br>
create folder: InternalLib</br>
copy: MessageInterface, NetCode projects</br>
and paste into folder</br>
UdpClient/InternalLib</br>
</br>
Step 3.</br>
before run program do in terminal:</br>
</br>
export LD_LIBRARY_PATH=lib/:$LD_LIBRARY_PATH</br>
then</br>
./main</br>

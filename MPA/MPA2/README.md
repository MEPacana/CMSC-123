# MPA2 (i think i shall never see a poem as lovely as in binary form)
### General Description (Read thoroughly until the Caveats Section):
When data is sent over the internet (movie, image, pdfs, emails, etc), it is sent as a series of packets - the data broken down into parts with a certain size. These packets contain information such as source address of the data, destination address, length of the data, the data itself, etc. An example of a packet (header information or the packet header) looks like the one below:
![alt tag](http://vle.upcebu.edu.ph/pluginfile.php/1765/mod_assign/intro/ip-header-2.png)


Check out http://www.thegeekstuff.com/2012/03/ip-protocol-header/ to read more on the packet header.

For this MP Assignment, you are to reconstruct packets "sent" into the actual message or data that is readable.  The packets are sent in binary format.

### Packet Description
Since this is a simple simulation, the packets in this MP Assignment will not contain all the information found in an actual packet. The data part of the packet will contain a line from a poem. This means that each packet represents a line from a poem. The title of the poem is represented with a packet.

Below shows a sample of 3 packets:

101011000110100101011001000101111011100101001011110100001001011100000000000000001010001011000000000000000100100001010100011011110010000001000001011101010111010001110101011011010110111000000000
00001111010110101111011110101110110000001000001000001010111011010000000000000000111001000001000000000000000100000100100101100110
1010110001101001010110010001011110111001010010111101000010010111111111111110100001110000101100100000000000000000
The packets will contain the following fields:
![alt tag](http://vle.upcebu.edu.ph/pluginfile.php/1765/mod_assign/intro/fields_green.jpg)

### Source and Destination Addresses

Both the addresses follow the IPv4 addresses. IPv4 addresses are 32-bit strings.  And they divided into 4 octets, separated by a dot. Each octet can take a value from 0 - 255 (since there 8 bits in each octet, the maximum value is 28 - 1, which 255). Some sample IP addresses that you may have encountered are of the form: 69.89.31.226 or 192.130.10.237.  This source/destination pair of addresses determines whether the packets belong to the same poem.  All packets with the same source/destination pair belong to one poem.
![alt tag](http://vle.upcebu.edu.ph/pluginfile.php/1765/mod_assign/intro/ip-address.png)
ip address sample

### Sequence Number

Since messages or data sent over the internet are broken down into a number of packets, there has to be a way for the recipient to know which packets belong to a particular data (datagram).  For our purpose, we will call this as a sequence number.  And it is 16 bits long.  This will be used for reconstruction. The sequence number indicates the ordering of the lines of the poem. A zero (0) sequence number means that the packet carries the title of the poem.  A packet that has a negative sequence number indicates that the packet is the "end-of-poem" packet. The absolute value of this number represents the total number of packets that belong to one poem. Say for instance a packet arrives with -10 as its sequence number, this means that there is a poem with 10 lines total, including the title.  This is going to be especially useful when there will be missing packets or missing lines from a certain poem. And for checking whether there are duplicate packets or lines received.

### Checksum

When packets are sent or transmitted over the internet, it is possible for the packets to get corrupted. A 0 might have turned into a 1 or vice versa or even an entire chunk corrupted and not just a bit. In order for the recipient to determine such an error in the transmission, a checksum is used.  Before a packet is transmitted, a value called the checksum is computed based on this packet using some algorithm.  Once the packet reaches its destination, the receiver computes for the checksum using the same algorithm and based on the packet received.  If the computed checksum and sent checksum match, then no such error occurred. But if they do not match, then an error has occurred while the packet was in transit.

### Checksum Algorithm for this MP Assignment

Say we have the following packet:

1010110001101001010110010001011110111001010010111101000010010111111111111110100001110000101100100000000000000000
Divide the packet into sub-parts containing 16 bits each.

1010110001101001/0101100100010111/1011100101001011/1101000010010111/1111111111101000/0111000010110010/0000000000000000
Before performing any computation, make sure that the checksum is set to zero first. This is because the checksum is computed based on the packet with the checksum set to zero initially. Make sure that you keep a copy of this checksum.

1010110001101001/0101100100010111/1011100101001011/0000000000000000/1111111111101000/0111000010110010/0000000000000000
Perform a series of additions on the 16-bit sub-parts of the packet. Since there will be a possibility for the sum to contain 17 bits due to a carry, we will use 17-bit numbers instead of 16.

01010110001101001 - adding the first two 16-bit sub-parts
00101100100010111
10000010110000000
If sum results in an overflow, add this bit to the sum (remove the most significant which is exactly the overflow).

10000010110000000 - that is the overflow
00000010110000000 - removing the overflow (we still have to have 17 bits)

00000010110000000
00000000000000001 - this is the overflow addition
00000010110000001 - this is the resulting sum
Add this new sum to the next 16-bit sub-part.  Repeat the process until all the 16-bit sub-parts have been added.

00000010110000001
01011100101001011 - third sub-part
01011111011001100

01011111011001100
00000000000000000 - fourth sub-part (this is actually the checksum default value)
01011111011001100

01011111011001100
01111111111101000 - fifth sub-part
11011111010110100

11011111010110100 - a carry overflow

01011111010110100
00000000000000001 - the overflow
01011111010110101

01011111010110101
00111000010110010 - sixth sub-part
10010111101100111

10010111101100111 - a carry overflow

00010111101100111
00000000000000001 - the overflow
00010111101101000

00010111101101000
00000000000000000 - seventh sub-part
00010111101101000 - this is the final sum, excluding the highlighted 0.
The final step is to get the 1's complement of the final sum (only its 16 bits, excluding the overflow).

0010111101101000 - final sum
1101000010010111 - 1's complement

checksum --> 1101000010010111
To check whether there was an error in transmitting this packet, compare this computed checksum with the transmitted checksum.

1101000010010111 - transmitted checksum take from the packet received
1101000010010111 - the computed checksum
Since they match, the packet is not corrupted.  If they do not match, then the packet is corrupted.

### Length of Data

This information is 16 bits long. This represents how long the data part is in bits.  This is the reason why the size of the data part is variable. It is dependent on the field Length of Data.

### Data

The data will be a line from a poem.  Each letter, punctuation or space of a line is converted and transmitted using its ASCII code written, of course, in binary. 

### Padding

Notice that there in computing for the checksum, the packet is divided into equal parts of 16 bits each.  Since the length of the data is variable, it is possible that the entire packet is not divisible by 16.  This means that the packet may or may not have a padding. In this assignment, the padding is simply a sequence of 0's.  The number of 0's is dependent on how many is needed to make the length of the entire packet divisible by 16. The padding is not part of the data.

Sample
Below is a sample packet.

101011000110100101011001000101111011100101001011110100001001011100000000000000011011101000001101000000010011100001010011011001010110000101110011011011110110111000100000011011110110011000100000011011010110100101110011011101000111001100100000011000010110111001100100001000000110110101100101011011000110110001101111011101110010000001100110011100100111010101101001011101000110011001110101011011000110111001100101011100110111001100000000
The first 32 bits represent the source IP address. The source IP address should be decoded and its 4-octet form, separated by dots, is 172.105.89.23.

101011000110100101011001000101111011100101001011110100001001011100000000000000011011101000001101000000010011100001010011011001010110000101110011011011110110111000100000011011110110011000100000011011010110100101110011011101000111001100100000011000010110111001100100001000000110110101100101011011000110110001101111011101110010000001100110011100100111010101101001011101000110011001110101011011000110111001100101011100110111001100000000
The second set of 32 bits represents the destination IP address.  Its 4-octet form, separated by dots, is 185.75.208.151.

101011000110100101011001000101111011100101001011110100001001011100000000000000011011101000001101000000010011100001010011011001010110000101110011011011110110111000100000011011110110011000100000011011010110100101110011011101000111001100100000011000010110111001100100001000000110110101100101011011000110110001101111011101110010000001100110011100100111010101101001011101000110011001110101011011000110111001100101011100110111001100000000
The next 16 bits represent the sequence number.  And this packet is sequence number 1.  Recall that the sequence numbers start with 0, the packet that represents the title.

101011000110100101011001000101111011100101001011110100001001011100000000000000011011101000001101000000010011100001010011011001010110000101110011011011110110111000100000011011110110011000100000011011010110100101110011011101000111001100100000011000010110111001100100001000000110110101100101011011000110110001101111011101110010000001100110011100100111010101101001011101000110011001110101011011000110111001100101011100110111001100000000
The next 16 bits represent the checksum.  Do not forget that the checksum of a packet is computed with this set of bits set to 0.

101011000110100101011001000101111011100101001011110100001001011100000000000000011011101000001101000000010011100001010011011001010110000101110011011011110110111000100000011011110110011000100000011011010110100101110011011101000111001100100000011000010110111001100100001000000110110101100101011011000110110001101111011101110010000001100110011100100111010101101001011101000110011001110101011011000110111001100101011100110111001100000000
The next 16 bits represent the length of the data. Converting the above 16 bits gives us 312.  This means that the data part is composed of 312 bits, shown below.

101011000110100101011001000101111011100101001011110100001001011100000000000000011011101000001101000000010011100001010011011001010110000101110011011011110110111000100000011011110110011000100000011011010110100101110011011101000111001100100000011000010110111001100100001000000110110101100101011011000110110001101111011101110010000001100110011100100111010101101001011101000110011001110101011011000110111001100101011100110111001100000000
The data part should be converted to actual characters that will form the line from a poem where this packet belongs to.  Each character is represented with 8 bits.

101011000110100101011001000101111011100101001011110100001001011100000000000000011011101000001101000000010011100001010011011001010110000101110011011011110110111000100000011011110110011000100000011011010110100101110011011101000111001100100000011000010110111001100100001000000110110101100101011011000110110001101111011101110010000001100110011100100111010101101001011101000110011001110101011011000110111001100101011100110111001100000000
The last 8 bits are simply padded data. They do not represent any information. They are used to make sure that the size of the entire packet is divisible by 16. This is needed for the checksum algorithm described in an earlier section.

### Implementation

### Representation

In this assignment, a poem has been divided into packets.  A poem should be represented with a use of a list of packets.  The entire collection of poems should be represented as a list of list of packets (list < list<packets> >). You may use available c++ library in solving the problem.  The bitset is especially useful.

### Input

The input to this MP Assignment is a file.  The file will contain a number of lines. Each of these lines represents a packet written in binary.  The lines are not necessarily arranged in the correct order they appear in a poem.

### Output

The output is the reconstructed/reassembled poems.  This should be written in a file named "poems.in".  Write the title first. In the next line, write the source/destination pair followed by the lines from the poem. Since the input may contain more than one poem, write the poems in the order that they are found in the input file.  Since we use the source/destination addresses to identify the poems, take note of the instances a new source/destination pair is read in the file.

Below is a sample output.

To Autumn
172.105.89.23/185.75.208.151
Season of mists and mellow fruitfulness,
Close bosom-friend of the maturing sun;
Conspiring with him how to load and bless
With fruit the vines that round the thatch-eaves run;
To bend with apples the moss'd cottage-trees,
And fill all fruit with ripeness to the core;
To swell the gourd, and plump the hazel shells
With a sweet kernel; to set budding more,
And still more, later flowers for the bees,
Until they think warm days will never cease,
For Summer has o'er-brimm'd their clammy cells.
Who hath not seen thee oft amid thy store?
Sometimes whoever seeks abroad may find
Thee sitting careless on a granary floor,
Thy hair soft-lifted by the winnowing wind;
Or on a half-reap'd furrow sound asleep,
Drows'd with the fume of poppies, while thy hook
Spares the next swath and all its twined flowers:
And sometimes like a gleaner thou dost keep
Steady thy laden head across a brook;
Or by a cider-press, with patient look,
Thou watchest the last oozings hours by hours.
Where are the songs of Spring? Ay, where are they?

--------------------------------------------------------------------------------

If
15.90.247.174/192.130.10.237
If you can keep your head when all about you
Are losing theirs and blaming it on you,
If you can trust yourself when all men doubt you,
But make allowance for their doubting too;
If you can wait and not be tired by waiting,
Or being lied about, don't deal in lies,
Or being hated, don't give way to hating,
And yet don't look too good, nor talk too wise:
If you can dream — and not make dreams your master;
If you can think — and not make thoughts your aim;
If you can meet with Triumph and Disaster
And treat those two impostors just the same;
If you can bear to hear the truth you've spoken
Twisted by knaves to make a trap for fools,
Or watch the things you gave your life to, broken,
And stoop and build 'em up with worn-out tools:
If you can make one heap of all your winnings
And risk it on one turn of pitch-and-toss,
And lose, and start again at your beginnings
And never breathe a word about your loss;
If you can force your heart and nerve and sinew
To serve your turn long after they are gone,
And so hold on when there is nothing in you

--------------------------------------------------------------------------------

Sonnet 18
241.110.48.219/24.238.133.94
Shall I compare thee to a Summer's day?
Thou art more lovely and more temperate:
Rough winds do shake the darling buds of May,
And Summer's lease hath all too short a date:
Sometime too hot the eye of heaven shines,
And oft' is his gold complexion dimm'd;
And every fair from fair sometime declines,
By chance or nature's changing course untrimm'd:
But thy eternal Summer shall not fade
Nor lose possession of that fair thou owest;
Nor shall Death brag thou wanderest in his shade,
When in eternal lines to time thou growest:
So long as men can breathe, or eyes can see,
So long lives this, and this gives life to thee.

--------------------------------------------------------------------------------

Hope is the Thing With Feathers
182.168.190.168/225.180.61.240
Hope Is The Thing With Feathers
Hope is the thing with feathers
That perches in the soul,
And sings the tune without the words,
And never stops at all.
And sweetest in the gale is heard;
And sore must be the storm
That could abash the little bird
That kept so many warm.
I've heard it in the chilliest land
And on the strangest sea;
Yet, never, in extremity,
It asked a crumb of me.

--------------------------------------------------------------------------------

Sunset
137.51.74.118/71.125.44.47
Slowly the west reaches for clothes of new colors
which it passes to a row of ancient trees.
You look, and soon these two worlds both leave you
one part climbs toward heaven, one sinks to earth.
leaving you, not really belonging to either,
not so hopelessly dark as that house that is silent,
not so unswervingly given to the eternal as that thing
that turns to a star each night and climbs--
leaving you (it is impossible to untangle the threads)
your own life, timid and standing high and growing,
so that, sometimes blocked in, sometimes reaching out,
one moment your life is a stone in you, and the next, a star.
Caveats
In transmitting the packets, it cannot be avoided that some 

will be missing - failed to reach the recipient
missing packets or lines will have to represented in the output file as [line missing] or [title missing] in case the title is not received
will be received more than once - the case of duplicate packets received
make sure that duplicate packets or lines are removed from the list of packets
will be corrupted
corrupted packets or lines will have to represented in the output file as [line corrupted]

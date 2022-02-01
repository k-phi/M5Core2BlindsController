# Architecture

<!-- vscode-markdown-toc -->
* 1. [Static architecture](#Staticarchitecture)
* 2. [Call chains](#Callchains)
	* 2.1. [Startup device](#Startupdevice)
	* 2.2. [Enable and disable blinds](#Enableanddisableblinds)
	* 2.3. [Move blinds](#Moveblinds)
	* 2.4. [Display battery level](#Displaybatterylevel)
	* 2.5. [Power down by button](#Powerdownbybutton)
	* 2.6. [Power down after timeout](#Powerdownaftertimeout)
	* 2.7. [Power down because of low battery level](#Powerdownbecauseoflowbatterylevel)
* 3. [Component dependency chart](#Componentdependencychart)
* 4. [Volatilities](#Volatilities)
	* 4.1. [User based volatilities](#Userbasedvolatilities)
	* 4.2. [Time based volatilities](#Timebasedvolatilities)
* 5. [Contracts](#Contracts)
	* 5.1. [Contract overview](#Contractoverview)
	* 5.2. [Contract to component mapping](#Contracttocomponentmapping)
* 6. [Configuration](#Configuration)

<!-- vscode-markdown-toc-config
	numbering=true
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->

##  1. <a name='Staticarchitecture'></a>Static architecture

![Static Architecture](http://www.plantuml.com/plantuml/png/RP91ImCn48Nl-HK1p_iNfDrML6WlNIzIzZ0cmsumEod9H2dYVtSaMspgvXAOxxrvuP5LOeYS9wyx1dP6hwCP7QFX756fzExe114clGdJAH0ITtpsgACeW0Ol6dCXUkFTx_Mbj9pZq_wvrtSxDupy6159VLzhsvmSOKgxC4ZgRDdYXpEu1u81evXVqVlmMLZh7TbqouJKUm-OGeu6ryR8zdhn5XZANFpoflCrN00biWQBOPSSAm5la53_vSqDj3vZMNfuw5vAKVq_LcpLNFBcMflZwAn5wcrpNzUdwZARIbaNecxwMTOcfLP8Lhx53m00 "Static Architecture")

Utility components which can be used by any component are (not yet) required.

##  2. <a name='Callchains'></a>Call chains

###  2.1. <a name='Startupdevice'></a>Startup device

![CallChain Startup Device](http://www.plantuml.com/plantuml/png/RP512i8m44NtSue1rxs2L2kee2jNKboCxL23qsb9KiNR6oorQNNx__l9WqcT9-kxMZ0ZaUn6Hl7qYLhSyCCK3E3kHbkoL6FMr6sZhFxaNy9ekV2abGGctntt5rmSJ7NpMykiaFVp8obLR4DtPf7c2VbQZ9RkD-_vLL6mSo4Ehxo6S4EU_XR3bslf6Cf0NSanZgEu1WYEc2HBd9XzquaNJ9XerMl018xgqHHYFY9W3ixM02bh6Ixo1W00 "CallChain Startup Device")

###  2.2. <a name='Enableanddisableblinds'></a>Enable and disable blinds

![Call Chain Enable and Disable Blinds](http://www.plantuml.com/plantuml/png/NL3D2e904BxFKmnqzXN2rAWWJvr2Eephe4lhABjhuTitM11w6MQ-NvWqHF9nwXtcv7HqP0MFGhLZ96cmi67PCsUb2G3XQMKaJptcGpyEmX9lSLQ1PnD9MiS0rRcyF71tjMqNJvvPeFhQIn9gsIjtP-U6DrG5lwpXWY8TZE4Gb5B738qYDGN6l-0NcBb9AxG1asIFgrnONGk_pOSji541f2oDlkC3 "Call Chain Enable and Disable Blinds")

###  2.3. <a name='Moveblinds'></a>Move blinds

![Chall Chain Move Blinds](http://www.plantuml.com/plantuml/png/RL3D2i8m3BxdAGgUzmeoDqK5Tt5UP7WeDMp5B1rjDzdRMpQ6dNW9vFl9zv7KUMbztvB86qdJr2mACw38IFFJ0RYNvavQsOhSj9rXP5_waL1OL5voJGXGdOhpGsmkkcxyqI8oLBEza2nhj86x8v5vB_XEANGkm44zGhN7GIly0Q-7yfQJ3ddBwOnwNCGh34A-I9AjMAN2QeluEUWF7VU0M3kntq8G2oCdG8hy3E_y0000 "Chall Chain Move Blinds")

###  2.4. <a name='Displaybatterylevel'></a>Display battery level

###  2.5. <a name='Powerdownbybutton'></a>Power down by button

![Call Chain Display Battery Level](http://www.plantuml.com/plantuml/png/LOz12eD034NtEKMWQwzGh0fjGLTT5UaYsA13OvIPQ9dRTw08kWdy_puFaWSZRyieM9AaCv1Jh5oOXI8MPCO-Oiqh2q3uE9t9quZbDCwJijh3eZ1wxeoq5mPeRytzXQVQzODTFRD2M_7gEcv8gMUVs9D5fk_MNxgEGqXrMiUjt0o5BCcPb9XbPpo8u91s_2-4VTXHW9prdVxz0G00 "Call Chain Display Battery Level")

###  2.6. <a name='Powerdownaftertimeout'></a>Power down after timeout

###  2.7. <a name='Powerdownbecauseoflowbatterylevel'></a>Power down because of low battery level

![Call Chain Power Down after Timout](http://www.plantuml.com/plantuml/png/LO_12i9034Jl-Og0v_w2L5lmeY3OYuY7iCPsCPijkwcbV-zU2lKIPjwGWQcpKR8f23OavGpa5QznveHjd1NfRKLsFiJ90FB7wqY90ZOnZ55PxMQBC2PsHjeB0pnQ_dh75rBgEJrnTsUHEA_yu1pdNF0fyRB2Oi--7-meKsduAy2gskFs5RPcamBKhA-ov0S0 "Call Chain Power Down after Timout")

##  3. <a name='Componentdependencychart'></a>Component dependency chart

![Static Architecture](http://www.plantuml.com/plantuml/png/TPBDRi8m48Jl-nGhSUOL4B-YbU12Ua4HXwsp2bOT1zcR8jwU5O76ZkZHyytEUYpFer2Ghd5O28ark0ZcR8MDT841ue_r5mhKuAfjBgrdBuNS76DG1_dQgQVys7-USBApzLcsWTb3kUPVQtXFdceEoexiN7k5Skcih-9OHyJNo9g45iPmZ4erxFO28x4FoiLAPxyfCWvHprijNSTG7ZR5ryfPhN3AzDwUQQ2LS3gTOLRaJyrgGEP9flhRGMPEy53rZINjzs_24wU7XC9upMWtf3iUR7WWW3dxId_57G00 "Static Architecture")

##  4. <a name='Volatilities'></a>Volatilities

###  4.1. <a name='Userbasedvolatilities'></a>User based volatilities

This system is not intended to be used by other users with different requirements. However, other users would most likely require a different local mapping of the IoT devices. E.g. another user might want to map blinds by rooms instead of mapping them by an entire floor.

Another user might want to use different IoT devices for blinds exposing different REST endpoints or requiring a different protocol. And in addition to blinds they might want to control a different IoT category such as lights, speakers, etc.

For the above mentioned cases changing the HMI, BlindsManager, BlindsAccess or adding new components would be necessary. The changes would most likely remain confined within a few components and not require a totally new architecture or a rewrite of all components.

###  4.2. <a name='Timebasedvolatilities'></a>Time based volatilities

While the first version of the system will be implemented for one blind, it is the goal to control all blinds of an entire floor. The following requirements could arise in the future:

* Mapping blinds to two floors and switching between floors.
* Controlling lights by rooms, e.g. all lights in the living room.
* Starting / stopping Sonos speakers by rooms.
* Starting the vacuum cleaner.
* Suspending the ring tone of the door bell for a limited time.

The impacts of these changes on the architecture would be similar as described above for the user based volatilities.

##  5. <a name='Contracts'></a>Contracts

###  5.1. <a name='Contractoverview'></a>Contract overview

![Contracts](http://www.plantuml.com/plantuml/png/TPB1QiCm44Jl_WeTvRy8iNimj11meMTPsfe5UTTermwbvD-hE0rrKbj7pTFixA23g4iw3T5KJ9gSLoaA98NqwJoOfeOPFRJgT98xORuBay_C60oGwoBOLXDIRy92DtNv1mIKVQ9ZZWRbPJ49JqmeYyj3bcD42XKFWwEm6OP7eBj9TuKValZ80lkoA8_xQi_lV691HVu_uh9HsLE-h9iUzEWqSryVBb5sU8KPeYqtW4Lfw0J90wbTRy54uFKsHEogHvVWzxQwCRdHrSEHpv1gFfEzZb8SW2Tjw0rZn1QoRP1bamDGoF_X1m00 "Contracts")

###  5.2. <a name='Contracttocomponentmapping'></a>Contract to component mapping

![Contracts to Component Mapping](http://www.plantuml.com/plantuml/png/ZLHDIyD04BtdLopqaXxi3n0HFoeQQA5GGJp9D3l6nSrCs9sq5lM_kqtLPjl4cblotinxRsR8XHTmKfTMNJE9Wroy4WulPSM496eALMMeI1B_QgW21-KEdClQedAO2r1XCG5hUVLKchUcm92WUuOSLJR6fSbnBY2r_z5HxuaApvADLaYmi9ZEnOLAfHjsDXxk2DhuViQ2sIhZRvecUe-ZXybdvENA6j8XGWcaEyrmXVJJPB4XHqvoonxxOIzSzQC5t_EClH73XnAV7IFRynTmLQ1SWGJU-W4SXGuJNA9DXns41ibeXYuFsqhRAPWeh6qhujFM7C7XzzVhBITCj5LOyGhTc5UKRgJ4bCYrP3GrrfevXhRQDqdotmEwcsPgC375YzmwH6eXpIRy50WAT6hmY9lpQU5R7yVmCGXSvi6lLuEWi3uWz81RzGXCDbv7e_FkWprLjKU_utGUqZufNkCt6WS_-pYfJ_eaJLbPB8FV_QfHVSHdfqYFvoCgVoMDbnHbwUmVyzifEXktjllVEKLRFsuekeD_ZocvGDBXj_a5 "Contracts to Component Mapping")

##  6. <a name='Configuration'></a>Configuration

The following data structure is required to configure a blind. Instead of a class a struct is sufficient.

![Blind Configuration](http://www.plantuml.com/plantuml/png/JL114e8m3Bpt5NaA8oTdF3ZwWaf3oKn9i4rLXl7lOb4WfsIpsMnI9RLHSn_W48WTrC8j-Hojah0nJR0fmGKRjUm3mcHWZhCGAzn4LVeJjbfBP8obrGQn2XsIxnHso9ESTkRzLrmKfXtXjSl7ZLXSBQP-zEzWm0U6KctMWXqbwqh9JFUCHrU0gqPY3pIixK4IbHFdJHMocp_m0G00 "Blind Configuration")

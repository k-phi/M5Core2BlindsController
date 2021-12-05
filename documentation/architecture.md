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

![Chall Chain Move Blinds](http://www.plantuml.com/plantuml/png/LO_12e9048RlynG3dNs5C2Kgo4js2UcmwA1BuwpiheLltw18TXdu_s_cWqb3D3wEFMFU6Pwd5IpScp1ZAqq022yhW_6cnzprWnEIMCQ92JtLqKZB152TYyiJTrVRTl7aYGIgvRmmObhooXx4x3vhVwXh2a5htPwWkXtBUyvMrQibur6zgiKasUEV3FxIXYzIs8QP_km0AKcZxtu1 "Chall Chain Move Blinds")

###  2.4. <a name='Displaybatterylevel'></a>Display battery level

###  2.5. <a name='Powerdownbybutton'></a>Power down by button

![Call Chain Display Battery Level](http://www.plantuml.com/plantuml/png/LOz12eD034NtEKMWQwzGh0fjGLTT5UaYsA13OvIPQ9dRTw08kWdy_puFaWSZRyieM9AaCv1Jh5oOXI8MPCO-Oiqh2q3uE9t9quZbDCwJijh3eZ1wxeoq5mPeRytzXQVQzODTFRD2M_7gEcv8gMUVs9D5fk_MNxgEGqXrMiUjt0o5BCcPb9XbPpo8u91s_2-4VTXHW9prdVxz0G00 "Call Chain Display Battery Level")

###  2.6. <a name='Powerdownaftertimeout'></a>Power down after timeout

###  2.7. <a name='Powerdownbecauseoflowbatterylevel'></a>Power down because of low battery level

![Call Chain Power Down after Timout](http://www.plantuml.com/plantuml/png/LO_12i9034Jl-Og0v_w2L5lmeY3OYuY7iCPsCPijkwcbV-zU2lKIPjwGWQcpKR8f23OavGpa5QznveHjd1NfRKLsFiJ90FB7wqY90ZOnZ55PxMQBC2PsHjeB0pnQ_dh75rBgEJrnTsUHEA_yu1pdNF0fyRB2Oi--7-meKsduAy2gskFs5RPcamBKhA-ov0S0 "Call Chain Power Down after Timout")

##  3. <a name='Componentdependencychart'></a>Component dependency chart

![Static Architecture](http://www.plantuml.com/plantuml/png/RP7BRi8m44NtynKZiUONAbvLgKGsX4qLiHYSKR3gECYUKF7tZ0WqTiJsFexcseie5AHl7PP2OWqkWpbROIDzO83uQ_s50hMuxjfBvzbBAJV763H1ld6QgRR5zn5dEzkSvIimUwWsVBM62_BKS53lXvth_g1QEUlhEDKHyLNPaD3I68vHNONTNiP4742vM6ltH95nH3slMhcUeTf_beUriphXcEb3FDD09-5y_e7Pa7yrcm5P9caDrq4MJknnwfj8kWzIN0A0AMS2XnJoyCON05Ymh_NRxm00 "Static Architecture")

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

![Contracts](http://www.plantuml.com/plantuml/png/TP5DYiCm38NtEOMNwIrAcou2KoYa5t3iro1mf60h2MNetSSDbFvCe-txfFSaRPFQg6CVp5vOetMQYe9O4I_MmTGL9d9erEgO7eJvBKokISWRi6q3oaOZSMVyGjVLvWbuIkj4An8CfSCon7ymVbFSthBi0h7VIzzRzb_3o01-36dly5iI5oHXNKugmxhQoLbEaaX9_blSlfpi8r_MJGVTMStSzGSJGiqdH0VMyiLda1cnafdBUuTI3ncrvYE5G0sSvCqNlotOvw_z0G00 "Contracts")

###  5.2. <a name='Contracttocomponentmapping'></a>Contract to component mapping

![Contracts to Component Mapping](http://www.plantuml.com/plantuml/png/ZLJ1Ji904BttApRXWWVu06CCOeqseGb9lNWootQi6xSppUuK9Cg_knIHBhH2RyrxC--zUKqdZgNbkZJYdf2jLEm4atyfAq905gciAer55BaFZPMqiZo06QyD20kA9HO68caChLvB_TaCQ6ImRrA1I69OQWKPIwxTNaTyHS8_IzAv09GB0yEChPyKUSDEugi38TUkdx4WCaAxXsP9VihP15wcHcFk8vGIyqupL07kboosvC29CkIW7tPCLJzQq3FDoMdMT2gnwJZPaJ-FYm9uAjdprZDOWabm3bRvCeOjdOfMO6DQuN0xmRe4gZd1L1kZCr3aapTwwg_cfpGHWvaktldH0c0BQUxbKeco02i6Bx0jkONlZ9x3OydoJYbmJWoymlg4q0Fkr0CmsdeTZs-xFwjhKJjm1qvdtSUayDY_Q1ZyvdjKZ_eaTLaPABtVuwbnVSPdfqYFvpCg_oKDImgoTEuF-UqKdOjRxLvwfw3ryuQ2x-3YCqKJmDp_t7u0 "Contracts to Component Mapping")

##  6. <a name='Configuration'></a>Configuration

The following data structure is required to configure a blind. Instead of a class a struct is sufficient.

![Blind Configuration](http://www.plantuml.com/plantuml/png/JOvD4i8m24RtEGL7wUXU5vuWjbYPIOZoeml7kpVIZihgyGqy6DIocDS2kq8ymRxnXMQNRDGu9MIlS1H2jaZWbQ0NDx5ha3RV2BDQm1Cxl5CQIrPTjQjrMoOsAFZ04js_lFtuEwbuT-GH3rxFA16VJ8XdeDldoe0yzVSN "Blind Configuration")

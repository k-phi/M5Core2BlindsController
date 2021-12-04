# Architecture

## Static architecture

![Static Architecture](http://www.plantuml.com/plantuml/png/RP91ImCn48Nl-HK1p_iNfDrML6WlNIzIzZ0cmsumEod9H2dYVtSaMspgvXAOxxrvuP5LOeYS9wyx1dP6hwCP7QFX756fzExe114clGdJAH0ITtpsgACeW0Ol6dCXUkFTx_Mbj9pZq_wvrtSxDupy6159VLzhsvmSOKgxC4ZgRDdYXpEu1u81evXVqVlmMLZh7TbqouJKUm-OGeu6ryR8zdhn5XZANFpoflCrN00biWQBOPSSAm5la53_vSqDj3vZMNfuw5vAKVq_LcpLNFBcMflZwAn5wcrpNzUdwZARIbaNecxwMTOcfLP8Lhx53m00 "Static Architecture")

## Call chains

### Startup device

![CallChain Startup Device](http://www.plantuml.com/plantuml/png/RP512i8m44NtSue1rxs2L2kee2jNKboCxL23qsb9KiNR6oorQNNx__l9WqcT9-kxMZ0ZaUn6Hl7qYLhSyCCK3E3kHbkoL6FMr6sZhFxaNy9ekV2abGGctntt5rmSJ7NpMykiaFVp8obLR4DtPf7c2VbQZ9RkD-_vLL6mSo4Ehxo6S4EU_XR3bslf6Cf0NSanZgEu1WYEc2HBd9XzquaNJ9XerMl018xgqHHYFY9W3ixM02bh6Ixo1W00 "CallChain Startup Device")

### Enable and disable blinds

![Call Chain Enable and Disable Blinds](http://www.plantuml.com/plantuml/png/NL3D2e904BxFKmnqzXN2rAWWJvr2Eephe4lhABjhuTitM11w6MQ-NvWqHF9nwXtcv7HqP0MFGhLZ96cmi67PCsUb2G3XQMKaJptcGpyEmX9lSLQ1PnD9MiS0rRcyF71tjMqNJvvPeFhQIn9gsIjtP-U6DrG5lwpXWY8TZE4Gb5B738qYDGN6l-0NcBb9AxG1asIFgrnONGk_pOSji541f2oDlkC3 "Call Chain Enable and Disable Blinds")

### Move blinds

![Chall Chain Move Blinds](http://www.plantuml.com/plantuml/png/LO_12e9048RlynG3dNs5C2Kgo4js2UcmwA1BuwpiheLltw18TXdu_s_cWqb3D3wEFMFU6Pwd5IpScp1ZAqq022yhW_6cnzprWnEIMCQ92JtLqKZB152TYyiJTrVRTl7aYGIgvRmmObhooXx4x3vhVwXh2a5htPwWkXtBUyvMrQibur6zgiKasUEV3FxIXYzIs8QP_km0AKcZxtu1 "Chall Chain Move Blinds")

### Display battery level

### Power down by button

![Call Chain Display Battery Level](http://www.plantuml.com/plantuml/png/LOz12eD034NtEKMWQwzGh0fjGLTT5UaYsA13OvIPQ9dRTw08kWdy_puFaWSZRyieM9AaCv1Jh5oOXI8MPCO-Oiqh2q3uE9t9quZbDCwJijh3eZ1wxeoq5mPeRytzXQVQzODTFRD2M_7gEcv8gMUVs9D5fk_MNxgEGqXrMiUjt0o5BCcPb9XbPpo8u91s_2-4VTXHW9prdVxz0G00 "Call Chain Display Battery Level")

### Power down after timeout

### Power down because of low battery level

![Call Chain Power Down after Timout](http://www.plantuml.com/plantuml/png/LO_12i9034Jl-Og0v_w2L5lmeY3OYuY7iCPsCPijkwcbV-zU2lKIPjwGWQcpKR8f23OavGpa5QznveHjd1NfRKLsFiJ90FB7wqY90ZOnZ55PxMQBC2PsHjeB0pnQ_dh75rBgEJrnTsUHEA_yu1pdNF0fyRB2Oi--7-meKsduAy2gskFs5RPcamBKhA-ov0S0 "Call Chain Power Down after Timout")

## Volatilities

### User based volatilities

This system is not intended to be used by other users with different requirements. However, other users would most likely require a different local mapping of the IoT devices. E.g. another user might want to map blinds by rooms instead of mapping them by an entire floor.

Another user might want to use different IoT devices for blinds exposing different REST endpoints or requiring a different protocol. And in addition to blinds they might want to control a different IoT category such as lights, speakers, etc.

For the above mentioned cases changing the HMI, BlindsManager, BlindsAccess or adding new components would be necessary. The changes would most likely remain confined within a few components and not require a totally new architecture or a rewrite of all components.

### Time based volatilities

While the first version of the system will be implemented for one blind, it is the goal to control all blinds of an entire floor. The following requirements could arise in the future:

* Mapping blinds to two floors and switching between floors.
* Controlling lights by rooms, e.g. all lights in the living room.
* Starting / stopping Sonos speakers by rooms.
* Starting the vacuum cleaner.
* Suspending the ring tone of the door bell for a limited time.

The impacts of these changes on the architecture would be similar as described above for the user based volatilities.

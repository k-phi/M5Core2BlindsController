# Architecture

## Static architecture

![Static Architecture](http://www.plantuml.com/plantuml/png/TPB1JiCm44Jl_WfBdFCBg4qhA59xeITKvR3OgyIgiuxi3QX2-NUM11gIjBw-ySnwrgl44BcjlJuoi3Dw7Ktb60st4PLAPqSDHAZr9jHD82G-yiMZZg80Ahrep1_HJp4G8rdzfRISq-xmKkY7lIihVew8f3gbhXTr3kOyY7lrQ9EtoH6cj0-b33HuzNvR_7063q1GOXJdD_G-V8uyzuvicdCXlQIRvxnY2cqqk3P6qfP1Ms0Oc7Z90ovpmHquZB64TmVudsqbz1qIwd66tmfpt-8OicDkDjw9JN6J3zSNhFlPmNLFsQborY8LDdkSrgwcIyWcocbnQjRZRMrIQYMHyjE-0G00 "Static Architecture")

Utility components which can be used by any component are (not yet) required.

## Call chains

### Startup device

![CallChain Startup Device](http://www.plantuml.com/plantuml/png/RP512i8m44NtSue1rxs2L2kee2jNKboCxL23qsb9KiNR6oorQNNx__l9WqcT9-kxMZ0ZaUn6Hl7qYLhSyCCK3E3kHbkoL6FMr6sZhFxaNy9ekV2abGGctntt5rmSJ7NpMykiaFVp8obLR4DtPf7c2VbQZ9RkD-_vLL6mSo4Ehxo6S4EU_XR3bslf6Cf0NSanZgEu1WYEc2HBd9XzquaNJ9XerMl018xgqHHYFY9W3ixM02bh6Ixo1W00 "CallChain Startup Device")

### Enable and disable blinds

![Call Chain Enable and Disable Blinds](http://www.plantuml.com/plantuml/png/NL3D2e904BxFKmnqzXN2rAWWJvr2Eephe4lhABjhuTitM11w6MQ-NvWqHF9nwXtcv7HqP0MFGhLZ96cmi67PCsUb2G3XQMKaJptcGpyEmX9lSLQ1PnD9MiS0rRcyF71tjMqNJvvPeFhQIn9gsIjtP-U6DrG5lwpXWY8TZE4Gb5B738qYDGN6l-0NcBb9AxG1asIFgrnONGk_pOSji541f2oDlkC3 "Call Chain Enable and Disable Blinds")

### Move blinds

![Chall Chain Move Blinds](http://www.plantuml.com/plantuml/png/RP112i9034NtEKN0TQyWsXPKi2jNKbp4DjJ1D2qpQSNRErZ4MjmCJDvByiac67aRMi7iHl9-dMBHZOofEAq3GBWxxSbJYrdNzfsosicUmkYvCj966A3S5uSBhewkkTdECokKKtj1IWtxoCuiqZq-zMrLSGYn7Eqdb3cFhkASZ1PWRzPdukBEp_XK1eOwcbSAZD_6EOOO1vDaZJyXuEStuzFEFtWP2-R-s_ZcWwMyc02mOQtZfLy0 "Chall Chain Move Blinds")

### Display battery level

### Display WiFi connection status

### Power down by button

### Power down after timeout

![Call Chain Display Battery Level](http://www.plantuml.com/plantuml/png/LOz12eD034NtEKMWQwzGh0fjGLTT5UaYsA13OvIPQ9dRTw08kWdy_puFaWSZRyieM9AaCv1Jh5oOXI8MPCO-Oiqh2q3uE9t9quZbDCwJijh3eZ1wxeoq5mPeRytzXQVQzODTFRD2M_7gEcv8gMUVs9D5fk_MNxgEGqXrMiUjt0o5BCcPb9XbPpo8u91s_2-4VTXHW9prdVxz0G00 "Call Chain Display Battery Level")

## Component dependency chart

![Static Architecture](http://www.plantuml.com/plantuml/png/RP7B2i8m44NtynK3hlq5yGKgwCgL51TZEjHWcfPaglZt3bPjKjpUns5kCez2GRhQuL58hC55C5ShRAGB311lrhSKgCPLKxUDPoz7UJh6e0dobTDCiJtipZZPs-egcy3ieLZptHe-aAUAWtedTgvvGB5qrfTnh2FYjx8ceOKn7AEw2dj-ZP7OWtAnrEw58kE0-borT1thcIBjobcTSCxqFfvfe9DmEfrXDkIdPZCWooIj_Zh8meazJFqJIVT1Yai0CEQCu912tjxm0W1pzgL--mi0 "Static Architecture")

## Volatilities

### User based volatilities

Other users would most likely require a different local mapping of their blinds. Additionally, another user might want to group blinds by rooms or different floors and be able to switch between them.

Another user might want to use different IoT devices to control their blinds. These devices are exposing different REST endpoints or requiring a different protocol.

In addition to blinds they might want to control a different device category such as lights, speakers, etc. with the same remote control.

For the above mentioned cases changing the HMI, BlindsManager, BlindsAccess or adding new components would be necessary. The changes would most likely remain confined within a few components and not require a totally new architecture or a rewrite of all components.

### Time based volatilities

While the first version of the system will be implemented for one blind, it is the goal to control all blinds of an entire floor. The following requirements could arise in the future:

* Mapping blinds to two or more floors and switching between floors.
* Controlling lights (Shelly 2.5) by rooms, e.g. all lights in the living room.
* Starting / stopping Sonos speakers by rooms.
* Starting the vacuum cleaner.
* Suspending the ring tone of the door bell for a limited time.

The impacts of these changes on the architecture would be similar as described above for the user based volatilities.

## Contracts

### Contract overview

![Contracts](http://www.plantuml.com/plantuml/png/XLFHJiCm37pVL-In83vYsWRIf4diRSzUuWwBu4o9MpGX_XqlBIobBLILAlkkkSivMIQ1ACsRD-l04i5AMYo81MCD5irsvOcT-LWOVHfET69qHd5pGjcwwYu3RI1dmXcvhAqF2Sj6ad0kQo4lMd-EzL8lU5jt84rk93EFPzLvE9iOmKDF6sn9luKd6vZHoe6UgD_HCGHlA5qxwmx4GJhdy8xnkQxxNkq3v0nN8AfpsM6BVijxZ1PPUjBll7lk0I8Jd_8lrRJN3GYKVXEqk5A7bHfFOkmBn7lpYfU7pdSBli5Y7shEJT4BYlK8SMhSGpkF34UlxtTwUAt_6fUZDC_eGywBQhp_Z6qNzEZ4CWOVyWaSqZJpH7eBRYP_8kkuIsId5-GB "Contracts")

### Contract to component mapping

![Contracts to Component Mapping](http://www.plantuml.com/plantuml/png/XLLTYzim47pthn3a9Isz-m57ATVSzIEGq48VZZwLFNdZ4oTBHb9y3Mt_UzUMdQmY-n82GJiZpMXsHMvz01VsjHPtrWG7CdWHB2tgnXeqGMoXQPIfYi8_AzE0W_e4_WW7ZSAX360gZGLeRLz-rUftlq6PW6u74iLwfPKfnPz2q6TllAeCbe9mKM5ObyitFT1QLGhReE5hgQr7Nl31DdmTb0wq_fVh-K7mT6uYhSfCPXxlLUVXtaG6fvxkiLNqopn9Qmnbzw0-g-56ZzPgeNnNkOiW9kaqzWNTjzrkgEsqXJx35GJIEMomHRqstz59wiv0Eizxu3w0CzIcVijoskiz1E1-FRIu8eTBCkw3a4_WtefdFBoBlblGUsJt87Fb59rHf4PmK-rExNmoyAZfEwQ7tVgrTfNAppE6aFj3ATuBRTjO6Xt7Oz2sdy2KHfbxHM_fPF8OMUJAuulwkbsBnKPLJ-6BGpGCYMEx1GCLIIv-OlUU61xRSWdlslPHIlHUB4ZXa15cmAYUW4NdzVtVgwjZ3ZT2rOt6cZRu7hs-_Z3EoutOUsJLOzlEWLxfl1W5XcgQH7Gmx6BwKomcUe4v2ixI9YynGOcbUJovMTh3w6ICZpb9QNd84pWRmOJ4vY7A9SHCCwDF9vgHcSUkcbX8pfkzRNvGacboo9Xvrho4DTjYBiMdCKUJvXMtQ4hwi_mF "Contracts to Component Mapping")

## Configuration

The following data structures are required to configure the application and each blind. Instead of a classes it is sufficient to use structs.

![Configuration](http://www.plantuml.com/plantuml/png/XL4nJWD13Epl5QxpYX2Qf40wGIIWtEpwRYqvzhBsAWNYxrmkd22827SUpyZZyTeyL6z7XdkLWSPMWvDArqKEPd1N2bESeQivl7SmLSoXmigCqe-sJCAIQp2SGLOPWHBZdewepJSuQCMdt3pfINRoGCna65MIVGjy8Vi9KRRkvH7V6fhRByN7OdN39EalaqsCHi4490vVJg-mGtDNwTNeh7hvZ_1wY_1CoVEjuHPfp7w9ISLy3ci5rC_GGPKX1jaJNpW3Q_0f1VPbxKvwh175poUlKTBqj4y0 "Configuration")

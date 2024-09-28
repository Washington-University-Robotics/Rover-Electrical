We want a small PoE router to help manage the network overall and simplify the process of configuring devices and reading diagnostic data. The basic requirements are:

* builtin gateway/routing capability
* multiple ethernet ports
* PoE powered outputs

There are a few options that support this. The main brands (Mikrotik, Ubiquiti, TP Link, etc) all have their version of a small PoE powered gateway that can be used to network devices. The factors that go into this decision are:

* ease of power
* ease of integration
* cost

Mikrotik and TP Link follow the proper IEEE PoE standard of 48V, which means that it would be incompatible with our current PoE setup. This means that we would need to step down the voltage from 48V to the 24V required by the Rocket M2s. The Ubiquiti edgerouter is made to work with Ubiquiti's PoE system already.

Because of the power situation, we will choose the Ubiquiti EdgeRouter X, so that we can simplify the network powering and keep consistency through the network. By using Ubiquiti, we also gain the benefits of their ecosystem, including their UIs and network integration with their own products.
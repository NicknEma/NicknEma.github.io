+++
title = 'Math idioms: sign toggling'
date = 2024-05-31T13:41:53+02:00
tags = ["math", "notation"]
categories = ["explanation"]
draft = true
+++

Math notation is often very compact. Its building blocks, the very basic symbols that we all know, can be combined in various ways to express the most complex ideas. Even when you want to say something that isn't directly captured by the existing set of symbols, you don't need to create new ones; you can just get creative with the ones that are already there.

The cost of using a piece of notation _beyond its original/common meaning_ is that the _mental model that we associated with that piece of notation_ is no longer sufficient.

As an example, consider this expression:

\[\sum_{i=1}^{10}{i(-1)^i}\]

The big capital sigma (\(\sum)\) indicates a _summation_. It's a compact way of describing the sum of many terms. You may not be familiar with the _symbol_, but [the usage of it is pretty basic; better wording].

What's a little more mysterious is this factor \((-1)^i\). It shouldn't be a mystery [repetition] to anybody that it indicates a _power_, but does it _mean_ anything? Not at first glance.

The reason that it's not obvious (or at least it wasn't to me) is that, in my mind, all I see is a number elevated to some power, and my brain filters out the information that considers irrelevant, like _what_ number is elevated to _what_ power. I know that powers are "repeated multiplication". That's how I was taught powers in middle school, and even though the meaning can be extended for negative and fractionary exponents, that is still a good enough mental model for most things.

The trick here is that the mental model of repeated multiplication is too general [meh wording]. It's true that we are multiplying \(-1\) repeatedly, but what is the _effect_ of that? Multiplying a number by \(-1\) simply changes its sign (from positive to negative and vice versa). So multiplying \(-1\) by \(-1\) means switching the sign to \(-1\), which gives \(1\). Multiply by \(-1\) again, and you are back to \(-1\). Every other multiplication by \(-1\) we go back to where we started; it's simply a cycle:

\[
\begin{aligned}
(-1)^1 \quad &= \quad -1 \\
(-1)^2 \quad &= \quad  1 \\
(-1)^3 \quad &= \quad -1 \\
(-1)^4 \quad &= \quad  1 \\
(-1)^5 \quad &= \quad -1 \\
(-1)^6 \quad &= \quad  1 \\
&...
\end{aligned}
\]

In this case, a better mental model than "repeated multiplication" is "sign toggling". At each increase of the exponent, the sign is switched from - to + and then back to -.

This expression, then,

\[\sum_{i=1}^{10}{i(-1)^i}\]

simply means to sum all integers from 1 to 10, each time inverting the sign. In other words, it means to sum all _even_ integers from 1 to 10, and then subtract all _odd_ integers from 1 to 10:

\[\sum_{i=1}^{10}{i(-1)^i} = - 1 + 2 - 3 + 4 - 5 + 6 - 7 + 8 - 9 + 10\]

### The inclusion-exclusion principle

An example of a formula that talks about _adding or subtracting a quantity based on the "parity" of something_ is the [inclusion-exclusion principle](https://en.wikipedia.org/wiki/Inclusion%E2%80%93exclusion_principle):

<formula here>



+++
title = 'The Infinity of Lines and Numbers'
description = "Understanding shapes with an infinite amount of points and their implications."
date = 2024-04-06T16:43:01+01:00
tags = ["math", "infinity"]
categories = ["explanation"]
draft = true
+++

> “_Young man, in mathematics you don't understand things. You just get used to them._”
>
> – John von Neumann

This is a line:

{{<figure-dynamic dark-src="line_dm.png" light-src="line_lm.png" alt="A line." position="center">}}

I was introduced to this mathematical object when I was in elementary school. The teacher drew one on the blackboard, and then said "a line is composed of an infinite number of points. The dashes at the ends indicate that it continues on forever, in both directions".
At first, I was surprised by the mention of infinity. It's hard to _visualize_ something that is infinite; our poor mortal brains are not used to think about things that untangible. So, as you'd expect, I couldn't _see_ the line going on forever.
But _logically_, it made complete sense. _Since it never ends, you must need an infinite number of points to trace it completely_. It's kind of like two immortal creatures forever walking in opposite directions. Nobody will ever see all their footprints, but we know for sure that there will be an infinite amount of them.

If you are wondering "how do we know that lines are infinite?", I want to make it clear that _lines don't exist in the real world_. They only exist in our minds, and they are perfect mathematical objects that are exactly what we imagine them to be.

At the top of this page there is a drawing of a line; but that drawing is not at all like what I had in mind when I drew it. I was thinking of a _perfectly straight, infinitely thin and infinitely long_ sequence of points, and all I drew is just an _approximation_ of it. Like Magritte would say, "that is not a line".

{{<figure-dynamic dark-src="ceci_dm.png" light-src="ceci_lm.png" alt="Ceci n'est pas une ligne." position="center">}}

Put it simply, a line goes on forever because we want it to. It doesn't need a reason to be what it is, it simply _is_.

The next idea is the one of half-lines. The teacher then picked up a red-colored chalk and drew a dot on the line, like this:

{{<figure-dynamic dark-src="half-line_dm.png" light-src="half-line_lm.png" alt="A half-line." position="center">}}

They said "this is a half line. It goes on forever in one direction, but not in the other. This," and pointed to the red dot, "is the origin of the half-line. Just like a line, a half-line has an infinite amount of points".

If you understood lines, this one is easy. Instead of two creatures, it's only one that takes the neverending walk, leaving all of its infinite footprints.

I hope you're still with me, because now is when my mind exploded.

"If you pick _two_ points on a line, you get a segment":

{{<figure-dynamic dark-src="segment_dm.png" light-src="segment_lm.png" alt="A segment." position="center">}}

"A segment has ininitely many points too."

Huh? A segment, infinitely many points? It has a start and an end, and in no direction keeps on going forever. I can _draw_ a whole segment, without putting dashes at the endpoints. How can this have anything to do with infinity?

The answer lies in the fact that, as I stated before, geometrical shapes are exactly what we want them to be. More specifically, we want our _points_ to be infinitely small - _dimensionless_. We want them to be so small that no matter how close you can put two of them, there will always be some space in the middle. We want the immortal being to take steps so tiny that any finite number of them will not bring it _any_ closer to its destination. Actually, we want it to be unable to take any steps, because the smallest step you can think of is still too big. That's how small we want our points.

Of course, such a thing can never exist in the real universe. By merely _existing_, an object will occupy a 3-dimensional space, and have a size. But in our minds, we can imagine a thing that _exists_, but it doesn't _occupy space_.

So, infinitely many infinitely small points. I'm still confused and fascinated by it to this day.

With this knowledge, I want you to try and answer this question: given one of the endpoints of a segment, what is the _closest_ distinct point that stands on that segment?

{{<figure-dynamic dark-src="closest-point_dm.png" light-src="closest-point_lm.png"alt="Points on a segment." position="center">}}

What is the point that is so close, no other point will fit between it and the extreme of the segment?

Maybe it's obvious, maybe it isn't, but the only possible answer is that there isn't one. No matter which point you pick, there will _always_ be room for other points. In fact, there will be room for _infinitely many_ more points.

### The real number line

One thing that mathematicians like to do is to associate points with numbers. A number is like a name: it makes it clear that you're talking about _that specific thing_.

If you take a line (a series of infinitely many, infinitely small points) and somehow manage to associate every one of them with a number, you get what mathematicians call the _real number line_. The numbers associated to each point are called _real numbers_.

{{<figure-dynamic dark-src="real-line_dm.png" light-src="real-line_lm.png"alt="The real number line." position="center">}}

The assertions that we made earlier about half-lines and segments directly translate to subsets of the real numbers. For example, while reals are infinite, all _positive_ reals are too, just like all reals bigger than 7, and all reals bigger than four billions.

{{<figure-dynamic dark-src="real-line-with-half-lines_dm.png" light-src="real-line-with-half-lines_lm.png"alt="A superiorly illimited interval." position="center">}}

There are also an infinite amount of numbers that are bigger than -1 and smaller than 1, or bigger than 2 and smaller than 2.05.

{{<figure-dynamic dark-src="real-line-with-segments_dm.png" light-src="real-line-with-segments_lm.png" alt="A limited interval." position="center">}}

And, just like before, if I told you to find the biggest real number that is smaller than 5, you'd tell me that it doesn't exist.

The last implication that I'd like to explore is the fact that, following from all this, we can deduce that _not all sets of numbers have a maximum value or a minimum value_. This was casually presented in my analysis textbook and was given no apparent importance, yet I had to stop and think about it for quite some time, because it is _not obvious at all_.

Consider the set of all real numbers between 2 and 4:

{{<figure-dynamic dark-src="real-line-with-2-and-4_dm.png" light-src="real-line-with-2-and-4_lm.png" alt="2 and 4 on the real number line." position="center">}}

What is crucial here is what I mean when I say "between": are we talking about all numbers in that range _including_ 2 and 4, or _excluding them_? Do we want to only include one, but not the other? This sounds like a detail, but it is the heart of the problem.

If we _include_ 2 and 4 in the range, then 2 is the minimum and 4 is the maximum, and that's all well and good. But if, say, 2 is _excluded_ from the range, then we can no longer identify a smaller value, because that would be 2's _next_ real number - and as we said before, there is no such a thing.

We can still talk about the range being _inferiorly limited_ by 2, as it does not contain any number smaller than 2; but since 2 itself is not in the set, it can't be called the minimum of that set.

Why is this important? Well, first of all, there are so many advanced theorems that depend on the existence or the absence of minimums and maximums of certain sets; laws by which scientists derive algorithms to make computers work faster and better.

Second... it's just cool. How often do you find something that is so out of reach, yet still makes so much sense?

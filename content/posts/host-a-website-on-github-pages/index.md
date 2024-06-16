+++
title = 'Host a Website on GitHub Pages'
description = 'The shortest guide to hosting a website on GitHub you will probabily ever find.'
date = 2024-06-16T16:53:13+02:00
tags = ["github", 'website', 'host']
categories = ['quick guide']
draft = false
+++

_This post expects you to already be able to create a GitHub repository and push changes onto it._

Any GitHub repository can be hosted with GitHub Pages. Each GitHub account is allowed _1 user site_ and _unlimited project sites_. Both kinds will have a limit of 1GB of storage and of 100GB of monthly bandwidth.

For a repository to be hosted on GitHub Pages it must be _public_ (unless you have GitHub Pro). It must also include a file named `index.html`, which will be the main page of the website.

### Set up a user site

The repository needs to be called exactly `<account-name>.github.io`, where `<account-name>` is your actual account's name.

As soon as you push the creation of the `index.html` file, the hosting process will start. It may take a couple of minutes to finish.

The user site will be hosted at `https://<account-name>.github.io`.

The only way to _un-publish_ a user site is to change the repository's name.

### Set up a project site

To start hosting the website, open your repository's page on GitHub, then go to **Settings** > **Pages** > **Source**. Select a branch and click **Save**.

The project site will now be hosted at `https://<account-name>.github.io/<repository-name>`.

To _un-publish_ the site, open your repository's page on GitHub, then go to **Settings** > **Pages**. Click on the **three dots** and then on **Unpublish site**.

### Why this post?

Because _[brevity is beautiful](https://betterexplained.com/articles/brevity-is-beautiful/)_ and you shouldn't have to spend a lot of time learning how to click a few buttons.

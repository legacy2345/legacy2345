Contributing
============

We welcome pull requests from everyone.  That doesn't guarantee your
contribution will be accepted, but it will be evaluated.

How To Contribute
-----------------

Fork, then clone the repo.

    git clone git@github.com:your-username/legacy2345.git

Set up an out-of-tree build directory.

    mkdir build
    cd build

Generate the config files and config the build directory.

    ../legacy2345/autogen.sh
    make
    cd ../legacy2345

Make your changes. Add tests for your changes. Make the tests pass:

    make -C ../build check

Push to your fork and [submit a pull request][pr].

[pr]: https://github.com/legacy2345/v3/compare

At this point you're waiting on us. We like to at least comment on pull requests
within three business days (and, typically, one business day). We may suggest
some changes or improvements or alternatives.

Some things that will increase the chance that your pull request is accepted:

* Write tests.
* Follow our [style guide][style].
* Write a [good commit message][commit].

[style]: https://github.com/legacy2345/v3/tree/guides/style
[commit]: http://tbaggery.com/2008/04/19/a-note-about-git-commit-messages.html

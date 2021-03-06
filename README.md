# hypertrav

## what
`hypertrav` recursively lists files and directories as fast as possible. Think `find .` without any bells and whistles.

It's 1.5 times faster than GNU `find`, and 3.9 times faster user space wise.

![Benchmark of hypertrav running 1.5x faster than find](./docs/bench.png)

(benchmarked with [the amazing `hyperfine`](https://github.com/sharkdp/hyperfine))

## why
Intended for use with `fzf` or as a front end to any interactive narrowing feature.

Simply `hypertrav | fzf` or `export FZF_CTRL_T_COMMAND=hypertrav`.

## how

### usage
`hypertrav [root path]`.

No argument defaults to `hypertrav .`.

### build
Build with `make build` and move the created `bin/hypertrav` somewhere on your `$PATH`.

## meta

Including parallel reading for SSDs soon.

With :heart: and :green_salad: by @Exr0n.


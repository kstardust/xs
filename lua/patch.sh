#!/bin/sh
set -eu

cd "$(dirname "$0")"

if git -C src apply --check ../patch.diff 2>/dev/null; then
	git -C src apply ../patch.diff
	printf '%s\n' "Lua patch applied"
elif git -C src apply --reverse --check ../patch.diff 2>/dev/null; then
	printf '%s\n' "Lua patch already applied"
else
	printf '%s\n' "Lua patch does not apply cleanly" >&2
	exit 1
fi

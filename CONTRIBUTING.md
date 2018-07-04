VBA:BT is meant to be a series of blitzes culminating in a finished blitz hack.
Anyone is free to contribute to any one of the blitzes, and
both I (the organizer) and the contributors must follow the following rules:

## Rules

1) Any insertable resource made will be in the final game.
 - Edits may be made to improve quality later.
 - Only up to so many submissions will be used. For example, if 40 maps are submitted, only the first 30 will be used.
 - All resources submitted should be under a creative commons license, and will be available for public use post-blitz.

2) Strict version control will be used.
 - Adding any new assets must be done through a branch and pull request.
 - Each pull request should pass tests. See "Testing".

3) Only newly created open source assets will be used (with exceptions).
 - See subpoints on #1.
 - Engine hacks, the base project, and resources from VBA1 may be used.

## Becoming a Contributor and Claiming Work

[This is the organizational spreadsheet for VBA:BT](https://docs.google.com/spreadsheets/d/1l5rRaDtYh3Q0GIxvw5rzPL0ZUY6MJzXmSQXwc1TcwBg/edit?usp=sharing).
To become a contributor, add yourself on sheet 1.

If you're adding a resource, such as a mug, map, or music track, fill out an appropriate line on the second sheet.
Leave the "Claimed" column blank.

If you're claiming a chapter to work on, fill out the appropriate row on the third sheet.
Put the team member responsible for committing the changes and all other contributors (including yourself) in the indicated columns.
The character IDs you're allowed to work with are provided.

If you need a resource for your chapter, go to the resource claim, and used the `Claimed By?` column to claim the resource.

## Testing

1) ColorzCore should assemble the project without errors or warnings.
2) The game should boot and new games should transition into the first chapter without error.
3) The feature being added should appear to be functional.

<nav>
	<div class="title">Library Manager</div>
	<div class="items">
		<div></div>
		<!--  TODO: Switch icon between nf-md-view_list and nf-md-view_grid -->
		<div>󰕰</div>
		<div></div>
	</div>
</nav>

<style>
	nav {
		height: 80px;
		background-color: var(--dark-gray);
		display: flex;
		align-items: center;

		& div {
			height: 100%;
			width: 50%;

			padding: 0 20px;

			display: flex;
			align-items: center;

			user-select: none;
			-webkit-user-select: none;
			-ms-user-select: none;

			&:hover {
				cursor: default;
			}

			&.title {
				font-size: 40px;
				font-weight: bold;
				font-family: 'Oswald', sans-serif;
			}

			&.items {
				font-family: 'NFSymbols', monospace;
				font-size: 20px;

				justify-content: flex-end;

				& div {
					width: auto;

					display: flex;
					justify-content: center;
					align-items: center;

					&:last-child {
						padding-right: 0;
					}
				}
			}
		}
	}
</style>

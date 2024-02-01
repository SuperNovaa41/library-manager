<script lang="ts" context="module">
  export interface BookEntry {
    id: number;
    isbn: string;
    title: string;
    authors: string;
    imageurl: string;
    year_of_publication: number;
    progress: number; // TODO: add this field.
    page_length: number;
  }
</script>

<script lang="ts">
  export let entry: BookEntry;
</script>

<div class="container">
  {#if entry.progress == 0}
    <p class="progress unread">UNREAD</p>
  {:else if entry.progress < entry.page_length}
    <p class="progress reading">{entry.progress}/{entry.page_length}</p>
  {:else if entry.progress == entry.page_length}
    <p class="progress complete">COMPLETE</p>
  {:else}
    <p class="progress na">N/A</p>
  {/if}
  <div class="content">
    <div class="cover">
      <img src={entry.imageurl} alt="Book Cover" />
    </div>
    <div class="text">
      <p class="author">{entry.authors}</p>
      <p class="title">{entry.title}</p>
    </div>
  </div>
</div>

<style>
  .container {
    height: 389px;
    border-radius: 10px;
    background-color: color-mix(in srgb, transparent, var(--dark-gray) 50%);

    & .progress {
      display: flex;
      justify-content: center;
      align-items: center;

      width: 100%;
      padding: 5px 0;
      border-radius: 10px 10px 0 0;
      width: 100%;

      font-family: "Rubik Mono One", sans-serif;

      &.unread {
        background-color: var(--dark-yellow);
      }

      &.reading {
        background-color: var(--dark-blue);
      }

      &.complete {
        background-color: var(--dark-green);
      }

      &.na {
        background-color: var(--dark-red);
      }
    }

    & .content {
      padding: 10px;

      & .cover {
        width: 100%;
        aspect-ratio: 0.666667;
        border-radius: 10px;
        background-color: var(--background);

        & img {
          vertical-align: middle;
          width: 100%;
          height: 100%;
          object-fit: cover;
          border-radius: 10px;
        }
      }

      & .text {
        width: 100%;
        height: 25%;
        margin-top: 5px;

        & .author {
          font-family: "Oswald", sans-serif;
          color: var(--light-gray);
          line-clamp: 1;
          display: -webkit-box;
          -webkit-line-clamp: 1;
          -webkit-box-orient: vertical;
          text-overflow: ellipsis;
          overflow: hidden;
        }

        & .title {
          font-family: "Merriweather Sans", sans-serif;
          font-weight: bold;
          line-clamp: 2;
          display: -webkit-box;
          -webkit-line-clamp: 2;
          -webkit-box-orient: vertical;
          text-overflow: ellipsis;
          overflow: hidden;
        }
      }
    }
  }
</style>

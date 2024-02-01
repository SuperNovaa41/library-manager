<script context="module" lang="ts">
  import { fetch, ResponseType } from "@tauri-apps/api/http";
</script>

<script lang="ts">
  import Book from "./Book.svelte";
  import type { BookEntry } from "./Book.svelte";

  interface Result {
    books: BookEntry[];
  }

  async function getBooks(): Promise<BookEntry[]> {
    const res = await fetch<Result>("http://localhost:18080/books", {
      method: "GET",
      timeout: 30,
      responseType: ResponseType.JSON,
    });

    return res.data.books;
  }

  const books = getBooks();
</script>

<div class="container">
  {#await books}
    <div class="status">
      <p>Loading...</p>
    </div>
  {:then books}
    <div class="books">
      {#each books as book}
        <Book entry={book} />
      {/each}
    </div>
  {:catch error}
    <div class="status">
      <p>{error}</p>
    </div>
  {/await}
</div>

<style>
  .container {
    height: 100%;
    width: 100%;
    margin-top: 80px;
    padding: 25px;

    & .books {
      height: 100%;
      width: 100%;
      display: grid;
      grid-template-columns: repeat(auto-fill, 200px);
      grid-gap: 25px;
    }
  }
</style>

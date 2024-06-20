'use client'

import Image from "next/image"
import Link from "next/link"
import React, { useState } from "react"
import './CustomHeader.css'

function HeaderButton({ href, children }: { href: string, children: React.ReactNode }) {
  return (
    <div className="flex items-center justify-center px-4 h-full bg-lime-300 bg-opacity-0 hover:bg-opacity-40 transition">
      <Link href={href} className="flex items-center h-full text-3xl md:text-2xl lg:text-3xl">
        {children}
      </Link>
    </div>
  );
}

export default function CustomHeader() {
  const [isOpen, setIsOpen] = useState(true);

  return (
    <>
      <div className="flex justify-between w-full h-16 md:h-18 lg:h-20 border-b border-color border-opacity-100 bg-lime-100 fixed top-0 left-0 z-50">
        <Link href="/" className="flex items-center h-full">
          <Image
            src="/ogame.png"
            width={1000}
            height={1000}
            alt="ogame's icon"
            style={{ width: 'auto', height: '100%' }}
          />
        </Link>
        <div className="hidden md:flex">
          <HeaderButton href="/">Top</HeaderButton>
          <HeaderButton href="/aboutme">About me</HeaderButton>
          <HeaderButton href="/works">Works</HeaderButton>
          <HeaderButton href="/blog">Blog</HeaderButton>
        </div>
        <div className="flex md:hidden">
          <div className="w-full aspect-square flex justify-center items-center">
            <div
              className={"burgerbtn " + (isOpen ? "active" : "")}
              onClick={() => { setIsOpen(!isOpen) }}
            >
              <span />
              <span />
              <span />
            </div>
          </div>
        </div>
      </div>
      <div className={`fixed top-16 ${isOpen ? "left-0" : "left-full"} w-full h-full bg-lime-50 z-50 transition-all duration-500`}>
        <div className="flex flex-col justify-center items-center p-10">
          <Link 
            href="/" 
            className="flex items-center h-full text-3xl md:text-2xl lg:text-3xl py-8"
            onClick={()=>{setIsOpen(false);}}
          >
            <div className="p-2 border-b border-black">Top</div>
          </Link>
          <Link 
            href="/aboutme" 
            className="flex items-center h-full text-3xl md:text-2xl lg:text-3xl py-8"
            onClick={()=>{setIsOpen(false);}}
          >
            <div className="p-2 border-b border-black">About me</div>
          </Link>
          <Link 
            href="/works" 
            className="flex items-center h-full text-3xl md:text-2xl lg:text-3xl py-8"
            onClick={()=>{setIsOpen(false);}}
          >
            <div className="p-2 border-b border-black">Works</div>
          </Link>
          <Link 
            href="/blog" 
            className="flex items-center h-full text-3xl md:text-2xl lg:text-3xl py-8"
            onClick={()=>{setIsOpen(false);}}
          >
            <div className="p-2 border-b border-black">Blog</div>
          </Link>
        </div>
      </div>
    </>
  );
}
